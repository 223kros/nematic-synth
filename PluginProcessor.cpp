#include "PluginProcessor.h"
#include "PluginEditor.h"

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
    return juce::String (p.section == 0 ? "ATMOS - " : "ROMANTICO - ") + p.cat + " - " + p.name;
}

void NematicProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    NematicEngine::Snap snap;
    for (size_t i = 0; i < snap.size(); ++i) snap[i] = raw[i]->load();

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
        }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NematicProcessor();
}
