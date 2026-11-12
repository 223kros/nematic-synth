#include "PluginProcessor.h"
#include "PluginEditor.h"

// Genera en segundo plano las fuentes de audio incluidas, para que el plugin abra rapido.
class NematicProcessor::Builder : public juce::Thread
{
public:
    explicit Builder (NematicProcessor& o) : juce::Thread ("Nematic sources"), owner (o) {}

    void run() override
    {
        for (int i = 0; i < granular_sources::kBuiltIn && ! threadShouldExit(); ++i)
            owner.installBuiltIn (i, granular_sources::make (i));
    }

private:
    NematicProcessor& owner;
};

juce::AudioProcessorValueTreeState::ParameterLayout NematicProcessor::createLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for (const auto& d : paramDefs())
    {
        juce::NormalisableRange<float> range (d.mn, d.mx, d.step, d.skew);
        layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { d.id, 1 }, d.name, range, d.def));
    }
    return layout;
}

NematicProcessor::NematicProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "STATE", createLayout())
{
    const auto& defs = paramDefs();
    for (size_t i = 0; i < defs.size(); ++i)
        raw[i] = apvts.getRawParameterValue (defs[i].id);
    for (auto& s : scope) s.store (0.f);
    applyPreset (0);

    builder = std::make_unique<Builder> (*this);
    builder->startThread (juce::Thread::Priority::low);
}

NematicProcessor::~NematicProcessor()
{
    if (builder != nullptr)
        builder->stopThread (8000);
}

void NematicProcessor::installBuiltIn (int idx, std::shared_ptr<SampleData> s)
{
    if (idx < 0 || idx >= granular_sources::kBuiltIn) return;
    {
        const juce::SpinLock::ScopedLockType sl (sampleLock);
        builtIn[(size_t) idx].swap (s);
    }
    // 's' ahora contiene el valor anterior (vacio) y se libera fuera del lock
}

void NematicProcessor::prepareToPlay (double sampleRate, int)
{
    engine.prepare (sampleRate);
}

bool NematicProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void NematicProcessor::applyPreset (int index)
{
    const auto& list = presets();
    if (index < 0 || index >= (int) list.size()) return;
    const auto& defs = paramDefs();
    for (size_t i = 0; i < defs.size(); ++i)
        if (auto* par = apvts.getParameter (defs[i].id))
            par->setValueNotifyingHost (par->convertTo0to1 (list[(size_t) index].v[i]));
}

void NematicProcessor::setCurrentProgram (int index)
{
    const int count = (int) presets().size();
    if (index < 0 || index >= count) return;
    currentProgram.store (index);
    applyPreset (index);
}

const juce::String NematicProcessor::getProgramName (int index)
{
    const auto& list = presets();
    if (index < 0 || index >= (int) list.size()) return {};
    const auto& p = list[(size_t) index];
    return juce::String (sectionName (p.section)) + " - " + p.cat + " - " + p.name;
}

void NematicProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    NematicEngine::Snap snap;
    for (size_t i = 0; i < snap.size(); ++i) snap[i] = raw[i]->load();

    // el lock se mantiene durante todo el bloque: asi el sample no se libera mientras suena
    const juce::SpinLock::ScopedTryLockType sampleGuard (sampleLock);
    const SampleData* src = nullptr;
    if (sampleGuard.isLocked())
    {
        const int si = juce::jlimit (0, granular_sources::kBuiltIn, (int) std::lround (snap[P_GSRC]));
        src = si >= granular_sources::kBuiltIn ? userSample.get() : builtIn[(size_t) si].get();
    }
    engine.setSource (src);

    int pos = 0;
    const int total = buffer.getNumSamples();
    for (const auto meta : midi)
    {
        const int t = juce::jlimit (0, total, meta.samplePosition);
        if (t > pos)
        {
            engine.render (buffer, pos, t - pos, snap);
            pos = t;
        }
        engine.handleMidi (meta.getMessage(), snap);
    }
    if (total > pos) engine.render (buffer, pos, total - pos, snap);
    midi.clear();

    // muestras para el visualizador
    const float* l = buffer.getReadPointer (0);
    int sp = scopePos.load();
    for (int i = 0; i < total; ++i)
    {
        if (++scopeCounter >= 8)
        {
            scopeCounter = 0;
            scope[(size_t) sp].store (l[i]);
            sp = (sp + 1) % kScopeSize;
        }
    }
    scopePos.store (sp);
}

// ---------------------------------------------------------------------------
//  Sample propio del usuario
// ---------------------------------------------------------------------------
bool NematicProcessor::loadUserSample (const juce::File& file)
{
    juce::AudioFormatManager fm;
    fm.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader (fm.createReaderFor (file));
    if (reader == nullptr || reader->lengthInSamples < 64 || reader->sampleRate <= 0.0)
        return false;

    const int len = (int) std::min<juce::int64> (reader->lengthInSamples, (juce::int64) (reader->sampleRate * 60.0));
    const int nch = (int) std::min<unsigned int> (reader->numChannels, 2u);

    auto s = std::make_shared<SampleData>();
    s->buf.setSize (nch, len);
    s->buf.clear();
    if (! reader->read (&s->buf, 0, len, 0, true, nch > 1))
        return false;
    s->rate = reader->sampleRate;
    s->name = file.getFileNameWithoutExtension();

    // normaliza para que cada sample suene a un nivel parecido
    float peak = 0.0001f;
    for (int c = 0; c < nch; ++c) peak = std::max (peak, s->buf.getMagnitude (c, 0, len));
    s->buf.applyGain (0.85f / peak);

    {
        const juce::SpinLock::ScopedLockType sl (sampleLock);
        userSample.swap (s);
    }
    apvts.state.setProperty ("samplePath", file.getFullPathName(), nullptr);
    return true;
}

juce::String NematicProcessor::getUserSampleName() const
{
    const juce::SpinLock::ScopedLockType sl (sampleLock);
    return userSample != nullptr ? userSample->name : juce::String();
}

std::shared_ptr<const SampleData> NematicProcessor::getSampleForDisplay (int idx) const
{
    const juce::SpinLock::ScopedLockType sl (sampleLock);
    if (idx >= granular_sources::kBuiltIn) return userSample;
    if (idx < 0) return {};
    return builtIn[(size_t) idx];
}

// ---------------------------------------------------------------------------
//  Tema de colores
// ---------------------------------------------------------------------------
ThemeSettings NematicProcessor::getTheme() const
{
    ThemeSettings t;
    const auto& st = apvts.state;
    t.hueA  = (float) (double) st.getProperty ("hueA",  (double) t.hueA);
    t.hueB  = (float) (double) st.getProperty ("hueB",  (double) t.hueB);
    t.hueC  = (float) (double) st.getProperty ("hueC",  (double) t.hueC);
    t.hueBg = (float) (double) st.getProperty ("hueBg", (double) t.hueBg);
    t.preset = (int) st.getProperty ("themePreset", 0);
    return t;
}

void NematicProcessor::setTheme (const ThemeSettings& t)
{
    auto st = apvts.state;
    st.setProperty ("hueA",  (double) t.hueA,  nullptr);
    st.setProperty ("hueB",  (double) t.hueB,  nullptr);
    st.setProperty ("hueC",  (double) t.hueC,  nullptr);
    st.setProperty ("hueBg", (double) t.hueBg, nullptr);
    st.setProperty ("themePreset", t.preset, nullptr);
}

juce::AudioProcessorEditor* NematicProcessor::createEditor()
{
    return new NematicEditor (*this);
}

void NematicProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    state.setProperty ("program", currentProgram.load(), nullptr);
    if (auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void NematicProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
        {
            auto tree = juce::ValueTree::fromXml (*xml);
            currentProgram.store (juce::jlimit (0, (int) presets().size() - 1, (int) tree.getProperty ("program", 0)));
            apvts.replaceState (tree);

            const juce::File f (tree.getProperty ("samplePath", "").toString());
            if (f.existsAsFile())
                loadUserSample (f);
        }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NematicProcessor();
}
