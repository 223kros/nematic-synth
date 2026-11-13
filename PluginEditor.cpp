#include "PluginEditor.h"

using namespace juce;

namespace
{
    constexpr int W = 1040, H = 760;

    struct ThemePreset { const char* name; float a, b, c, bg; };
    const ThemePreset kThemes[4] = {
        { "VIOLETA",   0.76f, 0.60f, 0.89f, 0.74f },
        { "ATARDECER", 0.93f, 0.07f, 0.80f, 0.90f },
        { "OCEANO",    0.54f, 0.62f, 0.48f, 0.60f },
        { "MENTA",     0.44f, 0.55f, 0.78f, 0.52f },
    };

    float wrap01 (float h) { return h - std::floor (h); }

    bool isAudioFile (const String& path)
    {
        const auto ext = File (path).getFileExtension().toLowerCase();
        return ext == ".wav" || ext == ".aif" || ext == ".aiff" || ext == ".mp3" || ext == ".flac" || ext == ".ogg";
    }

    int paramIndex (const char* id)
    {
        return paramIndexOf (id);
    }
}

// ---------------------------------------------------------------------------
//  Paleta y estilo
// ---------------------------------------------------------------------------
Palette Palette::from (const ThemeSettings& t)
{
    Palette p;
    p.bg1 = Colour::fromHSV (wrap01 (t.hueBg), 0.55f, 0.07f, 1.f);
    p.bg2 = Colour::fromHSV (wrap01 (t.hueBg + 0.03f), 0.65f, 0.16f, 1.f);
    p.accA = Colour::fromHSV (wrap01 (t.hueA), 0.62f, 1.0f, 1.f);
    p.accB = Colour::fromHSV (wrap01 (t.hueB), 0.65f, 1.0f, 1.f);
    p.accC = Colour::fromHSV (wrap01 (t.hueC), 0.60f, 1.0f, 1.f);
    return p;
}

void CleanLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int w, int h, float pos,
                                         float startAngle, float endAngle, Slider&)
{
    const auto b = Rectangle<float> ((float) x, (float) y, (float) w, (float) h).reduced (3.f);
    const float r = jmin (b.getWidth(), b.getHeight()) * 0.5f;
    const auto c = b.getCentre();
    const float angle = startAngle + pos * (endAngle - startAngle);
    const float arcR = r - 1.5f;

    Path track;
    track.addCentredArc (c.x, c.y, arcR, arcR, 0.f, startAngle, endAngle, true);
    g.setColour (Colours::white.withAlpha (0.10f));
    g.strokePath (track, PathStrokeType (2.5f, PathStrokeType::curved, PathStrokeType::rounded));

    Path val;
    val.addCentredArc (c.x, c.y, arcR, arcR, 0.f, startAngle, jmax (startAngle + 0.001f, angle), true);
    g.setGradientFill (ColourGradient (pal.accB, c.x - r, c.y + r, pal.accC, c.x + r, c.y - r, false));
    g.strokePath (val, PathStrokeType (2.5f, PathStrokeType::curved, PathStrokeType::rounded));

    const float br = arcR - 5.f;
    g.setColour (pal.bg2.darker (0.3f));
    g.fillEllipse (c.x - br, c.y - br, br * 2.f, br * 2.f);
    g.setColour (Colours::white.withAlpha (0.12f));
    g.drawEllipse (c.x - br, c.y - br, br * 2.f, br * 2.f, 1.f);

    const float px = c.x + std::sin (angle) * br * 0.66f;
    const float py = c.y - std::cos (angle) * br * 0.66f;
    g.setColour (Colours::white);
    g.fillEllipse (px - 2.f, py - 2.f, 4.f, 4.f);
}

void CleanLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int w, int h, float sliderPos,
                                         float, float, Slider::SliderStyle, Slider&)
{
    const float cy = (float) y + (float) h * 0.5f;
    const auto track = Rectangle<float> ((float) x + 7.f, cy - 3.f, (float) w - 14.f, 6.f);

    ColourGradient grad (Colour::fromHSV (0.f, 0.6f, 0.95f, 1.f), track.getX(), 0.f,
                         Colour::fromHSV (0.999f, 0.6f, 0.95f, 1.f), track.getRight(), 0.f, false);
    for (int i = 1; i < 12; ++i)
        grad.addColour ((double) i / 12.0, Colour::fromHSV ((float) i / 12.f, 0.6f, 0.95f, 1.f));
    g.setGradientFill (grad);
    g.fillRoundedRectangle (track, 3.f);

    g.setColour (Colours::white);
    g.fillEllipse (sliderPos - 7.f, cy - 7.f, 14.f, 14.f);
    g.setColour (Colours::black.withAlpha (0.35f));
    g.drawEllipse (sliderPos - 7.f, cy - 7.f, 14.f, 14.f, 1.f);
}

void CleanLookAndFeel::drawButtonBackground (Graphics& g, Button& b, const Colour& base, bool hover, bool down)
{
    const auto r = b.getLocalBounds().toFloat().reduced (0.5f);
    const bool on = b.getToggleState();
    if (on)
    {
        g.setColour (base.withAlpha (0.24f));
        g.fillRoundedRectangle (r, 7.f);
        g.setColour (base.withAlpha (0.9f));
        g.drawRoundedRectangle (r, 7.f, 1.2f);
    }
    else
    {
        g.setColour (Colours::white.withAlpha (down ? 0.12f : hover ? 0.08f : 0.04f));
        g.fillRoundedRectangle (r, 7.f);
        g.setColour (Colours::white.withAlpha (0.12f));
        g.drawRoundedRectangle (r, 7.f, 1.f);
    }
}

Font CleanLookAndFeel::getTextButtonFont (TextButton&, int buttonHeight)
{
    return Font (FontOptions (jmin (13.f, (float) buttonHeight * 0.46f), Font::bold));
}

// ---------------------------------------------------------------------------
//  Editor
// ---------------------------------------------------------------------------
NematicEditor::NematicEditor (NematicProcessor& p)
    : AudioProcessorEditor (&p), proc (p)
{
    setLookAndFeel (&laf);
    setSize (W, H);

    theme = proc.getTheme();
    laf.pal = Palette::from (theme);

    rawSrc = proc.apvts.getRawParameterValue ("gSrc");
    rawPos = proc.apvts.getRawParameterValue ("gPos");
    rawPosR = proc.apvts.getRawParameterValue ("gPosR");

    // secciones
    for (int i = 0; i < kNumSections; ++i)
    {
        secBtn[i].setButtonText (sectionName (i));
        secBtn[i].setClickingTogglesState (false);
        secBtn[i].onClick = [this, i]
        {
            section = i;
            searching = false;
            search.setText ({}, dontSendNotification);
            rebuildCategories();
            if (! rows.empty()) loadProgram (rows.front());
        };
        addAndMakeVisible (secBtn[i]);
    }

    prevBtn.onClick = [this]
    {
        const int n = (int) presets().size();
        loadProgram ((proc.getCurrentProgram() + n - 1) % n);
    };
    nextBtn.onClick = [this]
    {
        const int n = (int) presets().size();
        loadProgram ((proc.getCurrentProgram() + 1) % n);
    };
    addAndMakeVisible (prevBtn);
    addAndMakeVisible (nextBtn);

    // buscador
    search.setTextToShowWhenEmpty ("Buscar un sonido (ej: pad, 808, bell, verano...)", Colours::white.withAlpha (0.35f));
    search.setFont (Font (FontOptions (14.f)));
    search.onTextChange = [this]
    {
        searching = search.getText().trim().isNotEmpty();
        rebuildRows();
    };
    addAndMakeVisible (search);

    presetList.setModel (this);
    presetList.setRowHeight (28);
    presetList.setColour (ListBox::backgroundColourId, Colours::transparentBlack);
    presetList.setColour (ListBox::outlineColourId, Colours::transparentBlack);
    addAndMakeVisible (presetList);

    // perillas de sonido
    addKnob (soundKnobs, paramIndex ("cutoff"), "BRILLO");
    addKnob (soundKnobs, paramIndex ("reso"),   "RESO");
    addKnob (soundKnobs, paramIndex ("aA"),     "ATAQUE");
    addKnob (soundKnobs, paramIndex ("aD"),     "DECAY");
    addKnob (soundKnobs, paramIndex ("aS"),     "SUSTAIN");
    addKnob (soundKnobs, paramIndex ("aR"),     "RELEASE");
    addKnob (soundKnobs, paramIndex ("det"),    "DETUNE");
    addKnob (soundKnobs, paramIndex ("drive"),  "DRIVE");
    addKnob (soundKnobs, paramIndex ("chorus"), "CHORUS");
    addKnob (soundKnobs, paramIndex ("dMix"),   "DELAY");
    addKnob (soundKnobs, paramIndex ("vMix"),   "REVERB");
    addKnob (soundKnobs, paramIndex ("vol"),    "VOLUMEN");

    // perillas granulares
    addKnob (granKnobs, paramIndex ("gMix"),   "MEZCLA");
    addKnob (granKnobs, paramIndex ("gPos"),   "POSICION");
    addKnob (granKnobs, paramIndex ("gPosR"),  "AZAR POS");
    addKnob (granKnobs, paramIndex ("gSize"),  "TAMANO");
    addKnob (granKnobs, paramIndex ("gDens"),  "DENSIDAD");
    addKnob (granKnobs, paramIndex ("gPitch"), "TONO");
    addKnob (granKnobs, paramIndex ("gScat"),  "DISPERSION");
    addKnob (granKnobs, paramIndex ("gSpr"),   "ESTEREO");
    addKnob (granKnobs, paramIndex ("gRev"),   "REVERSA");
    addKnob (granKnobs, paramIndex ("gScan"),  "RECORRIDO");
    addKnob (granKnobs, paramIndex ("gShape"), "FORMA");

    // fuente granular
    for (int i = 0; i <= granular_sources::kBuiltIn; ++i)
        srcBox.addItem (granular_sources::nameOf (i), i + 1);
    srcBox.onChange = [this] { setSourceIndex (srcBox.getSelectedId() - 1); };
    addAndMakeVisible (srcBox);

    loadBtn.onClick = [this] { chooseSampleFile(); };
    addAndMakeVisible (loadBtn);

    keyBtn.setClickingTogglesState (true);
    keyAttach = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment> (proc.apvts, "gKey", keyBtn);
    addAndMakeVisible (keyBtn);

    // colores
    for (int i = 0; i < 4; ++i)
    {
        themeBtn[i].setButtonText (kThemes[i].name);
        themeBtn[i].onClick = [this, i]
        {
            theme.hueA = kThemes[i].a;
            theme.hueB = kThemes[i].b;
            theme.hueC = kThemes[i].c;
            theme.hueBg = kThemes[i].bg;
            theme.preset = i;
            hueSl[0].setValue (theme.hueA, dontSendNotification);
            hueSl[1].setValue (theme.hueB, dontSendNotification);
            hueSl[2].setValue (theme.hueC, dontSendNotification);
            hueSl[3].setValue (theme.hueBg, dontSendNotification);
            applyTheme (true);
        };
        addAndMakeVisible (themeBtn[i]);
    }

    const float vals[4] = { theme.hueA, theme.hueB, theme.hueC, theme.hueBg };
    for (int i = 0; i < 4; ++i)
    {
        hueSl[i].setSliderStyle (Slider::LinearHorizontal);
        hueSl[i].setTextBoxStyle (Slider::NoTextBox, true, 0, 0);
        hueSl[i].setRange (0.0, 1.0, 0.001);
        hueSl[i].setValue (vals[i], dontSendNotification);
        hueSl[i].onValueChange = [this]
        {
            theme.hueA = (float) hueSl[0].getValue();
            theme.hueB = (float) hueSl[1].getValue();
            theme.hueC = (float) hueSl[2].getValue();
            theme.hueBg = (float) hueSl[3].getValue();
            theme.preset = -1;
            applyTheme (true);
        };
        addAndMakeVisible (hueSl[i]);
    }

    // estado inicial
    const auto& list = presets();
    const int cur = jlimit (0, (int) list.size() - 1, proc.getCurrentProgram());
    section = list[(size_t) cur].section;
    cat = list[(size_t) cur].cat;
    rebuildCategories();
    syncFromProgram();
    applyTheme (false);

    setResizable (false, false);
    startTimerHz (30);
}

NematicEditor::~NematicEditor()
{
    stopTimer();
    setLookAndFeel (nullptr);
}

NematicEditor::Knob* NematicEditor::addKnob (OwnedArray<Knob>& arr, int paramIdx, const char* label)
{
    auto* k = arr.add (new Knob());
    const auto& d = paramDefs()[(size_t) paramIdx];
    k->label = label;
    k->slider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    k->slider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);
    k->slider.setRotaryParameters (MathConstants<float>::pi * 1.2f, MathConstants<float>::pi * 2.8f, true);
    k->slider.setPopupDisplayEnabled (true, true, this);
    k->slider.setDoubleClickReturnValue (true, (double) d.def);
    k->attach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (proc.apvts, d.id, k->slider);
    addAndMakeVisible (k->slider);
    return k;
}

Colour NematicEditor::sectionColour (int s) const
{
    switch (s)
    {
        case 0:  return laf.pal.accA;
        case 1:  return laf.pal.accC;
        case 2:  return laf.pal.accB;
        default: return laf.pal.accA.withRotatedHue (0.14f);
    }
}

void NematicEditor::refreshColours()
{
    const auto& pal = laf.pal;

    for (int i = 0; i < kNumSections; ++i)
    {
        secBtn[i].setColour (TextButton::buttonColourId, sectionColour (i));
        secBtn[i].setColour (TextButton::textColourOffId, Colours::white.withAlpha (0.7f));
        secBtn[i].setColour (TextButton::textColourOnId, Colours::white);
    }
    for (auto* b : catBtns)
    {
        b->setColour (TextButton::buttonColourId, sectionColour (section));
        b->setColour (TextButton::textColourOffId, Colours::white.withAlpha (0.65f));
        b->setColour (TextButton::textColourOnId, Colours::white);
    }
    for (auto* b : { &prevBtn, &nextBtn, &loadBtn, &keyBtn })
    {
        b->setColour (TextButton::buttonColourId, pal.accC);
        b->setColour (TextButton::textColourOffId, Colours::white.withAlpha (0.8f));
        b->setColour (TextButton::textColourOnId, Colours::white);
    }
    for (int i = 0; i < 4; ++i)
    {
        themeBtn[i].setColour (TextButton::buttonColourId, pal.accA);
        themeBtn[i].setColour (TextButton::textColourOffId, Colours::white.withAlpha (0.7f));
        themeBtn[i].setColour (TextButton::textColourOnId, Colours::white);
        themeBtn[i].setToggleState (theme.preset == i, dontSendNotification);
    }

    search.setColour (TextEditor::backgroundColourId, Colours::white.withAlpha (0.05f));
    search.setColour (TextEditor::textColourId, Colours::white);
    search.setColour (TextEditor::outlineColourId, Colours::white.withAlpha (0.12f));
    search.setColour (TextEditor::focusedOutlineColourId, pal.accA);
    search.setColour (TextEditor::highlightColourId, pal.accA.withAlpha (0.35f));
    search.setColour (CaretComponent::caretColourId, Colours::white);

    srcBox.setColour (ComboBox::backgroundColourId, Colours::white.withAlpha (0.05f));
    srcBox.setColour (ComboBox::textColourId, Colours::white);
    srcBox.setColour (ComboBox::outlineColourId, Colours::white.withAlpha (0.12f));
    srcBox.setColour (ComboBox::arrowColourId, pal.accC);

    laf.setColour (PopupMenu::backgroundColourId, pal.bg2);
    laf.setColour (PopupMenu::textColourId, Colours::white.withAlpha (0.85f));
    laf.setColour (PopupMenu::highlightedBackgroundColourId, pal.accA.withAlpha (0.35f));
    laf.setColour (PopupMenu::highlightedTextColourId, Colours::white);
    laf.setColour (ScrollBar::thumbColourId, pal.accA.withAlpha (0.45f));
    laf.setColour (BubbleComponent::backgroundColourId, pal.bg2);
    laf.setColour (TooltipWindow::textColourId, Colours::white);
}

void NematicEditor::applyTheme (bool save)
{
    laf.pal = Palette::from (theme);
    if (save) proc.setTheme (theme);
    refreshColours();
    sendLookAndFeelChange();
    repaint();
}

// ---------------------------------------------------------------------------
//  Presets: categorias, lista, seleccion
// ---------------------------------------------------------------------------
void NematicEditor::rebuildCategories()
{
    catBtns.clear();
    const auto cats = categoriesFor (section);
    if (cat.isEmpty() || ! cats.contains (cat))
        cat = cats.isEmpty() ? String() : cats[0];

    for (const auto& c : cats)
    {
        auto* b = catBtns.add (new TextButton (c));
        b->setClickingTogglesState (false);
        b->onClick = [this, c]
        {
            cat = c;
            searching = false;
            search.setText ({}, dontSendNotification);
            rebuildRows();
            refreshStates();
            if (! rows.empty()) loadProgram (rows.front());
        };
        addAndMakeVisible (b);
    }
    resized();
    refreshColours();
    rebuildRows();
    refreshStates();
}

void NematicEditor::rebuildRows()
{
    rows.clear();
    const auto q = search.getText().trim().toLowerCase();
    const auto& list = presets();
    for (int i = 0; i < (int) list.size(); ++i)
    {
        const auto& p = list[(size_t) i];
        if (q.isNotEmpty())
        {
            if (String (p.name).toLowerCase().contains (q) || String (p.cat).toLowerCase().contains (q)
                || String (sectionName (p.section)).toLowerCase().contains (q))
                rows.push_back (i);
        }
        else if (p.section == section && cat == p.cat)
            rows.push_back (i);
    }
    presetList.updateContent();
    presetList.repaint();
}

void NematicEditor::refreshStates()
{
    for (int i = 0; i < kNumSections; ++i)
        secBtn[i].setToggleState (i == section, dontSendNotification);
    for (auto* b : catBtns)
        b->setToggleState (b->getButtonText() == cat, dontSendNotification);
}

void NematicEditor::loadProgram (int index)
{
    proc.setCurrentProgram (index);
    syncFromProgram();
}

void NematicEditor::syncFromProgram()
{
    const int cur = proc.getCurrentProgram();
    const auto& list = presets();
    if (cur < 0 || cur >= (int) list.size()) return;
    shownProgram = cur;

    const auto& p = list[(size_t) cur];
    if (! searching && (p.section != section || cat != p.cat))
    {
        section = p.section;
        cat = p.cat;
        rebuildCategories();
    }
    refreshStates();
    presetList.repaint();

    for (size_t i = 0; i < rows.size(); ++i)
        if (rows[i] == cur) { presetList.scrollToEnsureRowIsOnscreen ((int) i); break; }
    repaint (nameRect);
}

void NematicEditor::paintListBoxItem (int row, Graphics& g, int w, int h, bool)
{
    if (row < 0 || row >= (int) rows.size()) return;
    const auto& p = presets()[(size_t) rows[(size_t) row]];
    const bool cur = rows[(size_t) row] == proc.getCurrentProgram();

    if (cur)
    {
        g.setColour (sectionColour (p.section).withAlpha (0.20f));
        g.fillRoundedRectangle (2.f, 1.f, (float) w - 4.f, (float) h - 2.f, 6.f);
        g.setColour (sectionColour (p.section));
        g.fillRoundedRectangle (2.f, 6.f, 3.f, (float) h - 12.f, 1.5f);
    }

    g.setColour (Colours::white.withAlpha (cur ? 1.f : 0.75f));
    g.setFont (Font (FontOptions (14.f, cur ? Font::bold : Font::plain)));
    g.drawText (p.name, 14, 0, w - 220, h, Justification::centredLeft);

    if (searching)
    {
        g.setColour (Colours::white.withAlpha (0.4f));
        g.setFont (Font (FontOptions (11.f)));
        g.drawText (String (sectionName (p.section)) + " - " + p.cat, w - 200, 0, 186, h, Justification::centredRight);
    }
}

void NematicEditor::listBoxItemClicked (int row, const MouseEvent&)
{
    if (row >= 0 && row < (int) rows.size())
        loadProgram (rows[(size_t) row]);
}

// ---------------------------------------------------------------------------
//  Granular: fuente y samples propios
// ---------------------------------------------------------------------------
void NematicEditor::setSourceIndex (int idx)
{
    idx = jlimit (0, granular_sources::kBuiltIn, idx);
    if (auto* par = proc.apvts.getParameter ("gSrc"))
        par->setValueNotifyingHost (par->convertTo0to1 ((float) idx));
}

void NematicEditor::chooseSampleFile()
{
    chooser = std::make_unique<FileChooser> ("Elegi un sample de audio (wav, mp3, aiff, flac)", File(),
                                             "*.wav;*.aif;*.aiff;*.mp3;*.flac;*.ogg");
    Component::SafePointer<NematicEditor> safe (this);
    chooser->launchAsync (FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles,
                          [safe] (const FileChooser& fc)
                          {
                              const auto f = fc.getResult();
                              if (safe != nullptr && f.existsAsFile())
                                  safe->loadSampleFile (f);
                          });
}

void NematicEditor::loadSampleFile (const File& f)
{
    if (proc.loadUserSample (f))
    {
        setSourceIndex (granular_sources::kBuiltIn);
        // la mezcla granular se sube sola si estaba apagada, para que se escuche enseguida
        if (auto* par = proc.apvts.getParameter ("gMix"))
            if (par->getValue() < 0.05f)
                par->setValueNotifyingHost (1.0f);
    }
    else
    {
        AlertWindow::showMessageBoxAsync (MessageBoxIconType::WarningIcon, "Vault",
                                          "No se pudo leer ese archivo de audio. Proba con un .wav.");
    }
}

bool NematicEditor::isInterestedInFileDrag (const StringArray& files)
{
    for (auto& f : files)
        if (isAudioFile (f)) return true;
    return false;
}

void NematicEditor::filesDropped (const StringArray& files, int, int)
{
    for (auto& f : files)
        if (isAudioFile (f)) { loadSampleFile (File (f)); break; }
}

void NematicEditor::rebuildPeaks()
{
    peaks.assign ((size_t) kPeakCols, 0.f);
    if (shownSample == nullptr) return;

    const auto& b = shownSample->buf;
    const int n = b.getNumSamples();
    if (n <= 0) return;

    for (int c = 0; c < kPeakCols; ++c)
    {
        const int s0 = (int) ((int64) c * n / kPeakCols);
        const int s1 = jmax (s0 + 1, (int) ((int64) (c + 1) * n / kPeakCols));
        const int stride = jmax (1, (s1 - s0) / 16);
        float m = 0.f;
        for (int ch = 0; ch < b.getNumChannels(); ++ch)
        {
            const float* d = b.getReadPointer (ch);
            for (int i = s0; i < s1 && i < n; i += stride)
                m = jmax (m, std::abs (d[i]));
        }
        peaks[(size_t) c] = m;
    }
}

void NematicEditor::timerCallback()
{
    if (proc.getCurrentProgram() != shownProgram)
        syncFromProgram();

    const int src = jlimit (0, granular_sources::kBuiltIn, (int) std::lround (rawSrc->load()));
    if (srcBox.getSelectedId() != src + 1)
        srcBox.setSelectedId (src + 1, dontSendNotification);

    const auto userName = proc.getUserSampleName();
    if (userName != shownUserName)
    {
        shownUserName = userName;
        srcBox.changeItemText (granular_sources::kBuiltIn + 1,
                               userName.isNotEmpty() ? "TU: " + userName : String (granular_sources::nameOf (granular_sources::kBuiltIn)));
    }

    auto s = proc.getSampleForDisplay (src);
    if (s.get() != shownSample.get() || src != shownSrc)
    {
        shownSample = s;
        shownSrc = src;
        rebuildPeaks();
    }

    repaint (scopeRect);
    repaint (waveRect);
}

// ---------------------------------------------------------------------------
//  Dibujo
// ---------------------------------------------------------------------------
void NematicEditor::drawPanel (Graphics& g, Rectangle<int> r, Colour edge)
{
    g.setColour (Colours::white.withAlpha (0.035f));
    g.fillRoundedRectangle (r.toFloat(), 12.f);
    g.setColour (edge.withAlpha (0.18f));
    g.drawRoundedRectangle (r.toFloat().reduced (0.5f), 12.f, 1.f);
}

void NematicEditor::paint (Graphics& g)
{
    const auto& pal = laf.pal;

    g.setGradientFill (ColourGradient (pal.bg2, 0.f, 0.f, pal.bg1, (float) W, (float) H, false));
    g.fillAll();

    // brillo suave de fondo
    g.setGradientFill (ColourGradient (pal.accA.withAlpha (0.10f), (float) W * 0.85f, 0.f, Colours::transparentBlack, (float) W * 0.55f, 260.f, true));
    g.fillRect (0, 0, W, 300);

    // titulo
    g.setColour (Colours::white);
    g.setFont (Font (FontOptions (30.f, Font::bold)));
    g.drawText ("VAULT", 24, 12, 260, 36, Justification::centredLeft);
    g.setColour (pal.accC);
    g.setFont (Font (FontOptions (12.f, Font::bold)));
    g.drawText ("SOUND LIBRARY", 26, 46, 200, 16, Justification::centredLeft);

    // nombre del preset actual
    const auto& list = presets();
    const int cur = jlimit (0, (int) list.size() - 1, proc.getCurrentProgram());
    const auto& p = list[(size_t) cur];
    g.setColour (Colours::white.withAlpha (0.05f));
    g.fillRoundedRectangle (nameRect.toFloat(), 8.f);
    g.setColour (sectionColour (p.section).withAlpha (0.5f));
    g.drawRoundedRectangle (nameRect.toFloat().reduced (0.5f), 8.f, 1.f);
    g.setColour (Colours::white);
    g.setFont (Font (FontOptions (17.f, Font::bold)));
    g.drawText (p.name, nameRect.reduced (14, 0).withTrimmedBottom (8), Justification::centredLeft);
    g.setColour (Colours::white.withAlpha (0.45f));
    g.setFont (Font (FontOptions (10.f)));
    g.drawText (String (sectionName (p.section)) + "  /  " + p.cat + "   -   " + String (cur + 1) + " de " + String ((int) list.size()),
                nameRect.reduced (14, 0).withTrimmedTop (22), Justification::centredLeft);

    // paneles
    drawPanel (g, panelColors, pal.accA);
    drawPanel (g, panelSound, pal.accB);
    drawPanel (g, panelGran, pal.accC);

    auto title = [&] (const String& t, int x, int y, Colour c)
    {
        g.setColour (c);
        g.setFont (Font (FontOptions (11.f, Font::bold)));
        g.drawText (t, x, y, 400, 16, Justification::centredLeft);
    };
    title ("COLORES", panelColors.getX() + 14, panelColors.getY() + 10, pal.accA);
    title ("SONIDO  -  ajusta el preset a tu gusto", panelSound.getX() + 14, panelSound.getY() + 8, pal.accB);
    title ("GRANULAR  -  convierte cualquier sample en texturas", panelGran.getX() + 14, panelGran.getY() + 8, pal.accC);

    static const char* hueNames[4] = { "PRINCIPAL", "SECUNDARIO", "BRILLO", "FONDO" };
    g.setFont (Font (FontOptions (10.f, Font::bold)));
    for (int i = 0; i < 4; ++i)
    {
        g.setColour (Colours::white.withAlpha (0.55f));
        g.drawText (hueNames[i], panelColors.getX() + 14, hueSl[i].getY(), 84, hueSl[i].getHeight(), Justification::centredLeft);
    }

    // etiquetas de perillas
    g.setFont (Font (FontOptions (10.f, Font::bold)));
    g.setColour (Colours::white.withAlpha (0.6f));
    for (auto* k : soundKnobs) g.drawText (k->label, k->labelRect, Justification::centred);
    for (auto* k : granKnobs)  g.drawText (k->label, k->labelRect, Justification::centred);

    // osciloscopio
    g.setColour (Colours::black.withAlpha (0.25f));
    g.fillRoundedRectangle (scopeRect.toFloat(), 10.f);
    {
        Path wave;
        const int start = proc.scopePos.load();
        const float cx = (float) scopeRect.getX(), cy = (float) scopeRect.getCentreY();
        const float sw = (float) scopeRect.getWidth(), sh = (float) scopeRect.getHeight() * 0.42f;
        for (int i = 0; i < NematicProcessor::kScopeSize; ++i)
        {
            const float v = jlimit (-1.f, 1.f, proc.scope[(size_t) ((start + i) % NematicProcessor::kScopeSize)].load() * 1.6f);
            const float x = cx + sw * (float) i / (float) (NematicProcessor::kScopeSize - 1);
            if (i == 0) wave.startNewSubPath (x, cy - v * sh); else wave.lineTo (x, cy - v * sh);
        }
        g.setGradientFill (ColourGradient (pal.accB, cx, cy, pal.accC, cx + sw, cy, false));
        g.strokePath (wave, PathStrokeType (1.6f));
    }
    g.setColour (Colours::white.withAlpha (0.10f));
    g.drawRoundedRectangle (scopeRect.toFloat().reduced (0.5f), 10.f, 1.f);

    // forma de onda del sample granular
    g.setColour (Colours::black.withAlpha (0.28f));
    g.fillRoundedRectangle (waveRect.toFloat(), 8.f);
    const float wx = (float) waveRect.getX(), ww = (float) waveRect.getWidth();
    const float wcy = (float) waveRect.getCentreY(), wh = (float) waveRect.getHeight() * 0.46f;

    if (shownSample == nullptr)
    {
        g.setColour (Colours::white.withAlpha (0.45f));
        g.setFont (Font (FontOptions (12.f)));
        g.drawText (shownSrc == granular_sources::kBuiltIn ? "Arrastra un sample aca o toca CARGAR SAMPLE" : "Preparando sonidos...",
                    waveRect, Justification::centred);
    }
    else
    {
        const float pos = rawPos->load(), posr = rawPosR->load();
        const float bx0 = jlimit (0.f, 1.f, pos - posr * 0.5f), bx1 = jlimit (0.f, 1.f, pos + posr * 0.5f);
        g.setColour (pal.accC.withAlpha (0.16f));
        g.fillRect (wx + bx0 * ww, (float) waveRect.getY() + 1.f, jmax (1.f, (bx1 - bx0) * ww), (float) waveRect.getHeight() - 2.f);

        g.setColour (pal.accB.withAlpha (0.85f));
        for (int c = 0; c < kPeakCols && c < (int) peaks.size(); ++c)
        {
            const float x = wx + (float) c * ww / (float) kPeakCols;
            const float m = jmax (0.01f, peaks[(size_t) c]) * wh;
            g.drawLine (x, wcy - m, x, wcy + m, 1.f);
        }
        g.setColour (pal.accC);
        g.fillRect (wx + pos * ww - 1.f, (float) waveRect.getY() + 1.f, 2.f, (float) waveRect.getHeight() - 2.f);
    }
    g.setColour (Colours::white.withAlpha (0.10f));
    g.drawRoundedRectangle (waveRect.toFloat().reduced (0.5f), 8.f, 1.f);

    // ayuda
    g.setColour (Colours::white.withAlpha (0.38f));
    g.setFont (Font (FontOptions (11.f)));
    g.drawText ("Toca notas MIDI para escuchar. Clic derecho o doble clic en una perilla: valor original.",
                panelColors.getX() + 14, panelColors.getBottom() - 38, panelColors.getWidth() - 24, 30, Justification::topLeft);
}

void NematicEditor::resized()
{
    const int margin = 24;
    const int leftW = 692;
    const int rightX = margin + leftW + 16;
    const int rightW = W - margin - rightX;

    // cabecera
    prevBtn.setBounds (W - 504, 18, 36, 34);
    nameRect = { W - 464, 14, 390, 42 };
    nextBtn.setBounds (W - 66, 18, 36, 34);

    // secciones
    const int secW = (leftW - 3 * 8) / 4;
    for (int i = 0; i < kNumSections; ++i)
        secBtn[i].setBounds (margin + i * (secW + 8), 84, secW, 36);

    // categorias (dos filas como maximo)
    int cx = margin, cy = 128;
    for (auto* b : catBtns)
    {
        if (cx + 80 > margin + leftW) { cx = margin; cy += 34; }
        b->setBounds (cx, cy, 80, 28);
        cx += 84;
    }

    search.setBounds (margin, 206, leftW, 28);
    presetList.setBounds (margin, 240, leftW, 210);

    // columna derecha
    scopeRect = { rightX, 84, rightW, 100 };
    panelColors = { rightX, 196, rightW, 254 };
    const int chipW = (rightW - 28 - 3 * 6) / 4;
    for (int i = 0; i < 4; ++i)
        themeBtn[i].setBounds (rightX + 14 + i * (chipW + 6), 232, chipW, 26);
    for (int i = 0; i < 4; ++i)
        hueSl[i].setBounds (rightX + 100, 270 + i * 32, rightW - 114, 26);

    // sonido
    panelSound = { margin, 462, W - 2 * margin, 112 };
    {
        const int kw = (panelSound.getWidth() - 24) / 12;
        int i = 0;
        for (auto* k : soundKnobs)
        {
            const int x = panelSound.getX() + 12 + i * kw;
            k->slider.setBounds (x + (kw - 58) / 2, panelSound.getY() + 26, 58, 58);
            k->labelRect = { x, panelSound.getY() + 88, kw, 16 };
            ++i;
        }
    }

    // granular
    panelGran = { margin, 586, W - 2 * margin, 160 };
    waveRect = { panelGran.getX() + 12, panelGran.getY() + 30, 380, 84 };
    srcBox.setBounds (panelGran.getX() + 12, panelGran.getY() + 122, 190, 28);
    loadBtn.setBounds (panelGran.getX() + 210, panelGran.getY() + 122, 114, 28);
    keyBtn.setBounds (panelGran.getX() + 332, panelGran.getY() + 122, 60, 28);
    {
        const int gx = panelGran.getX() + 416;
        const int kw = (panelGran.getRight() - 12 - gx) / 6;
        int i = 0;
        for (auto* k : granKnobs)
        {
            const int col = i % 6, row = i / 6;
            const int x = gx + col * kw;
            const int y = panelGran.getY() + 28 + row * 62;
            k->slider.setBounds (x + (kw - 46) / 2, y, 46, 46);
            k->labelRect = { x, y + 46, kw, 14 };
            ++i;
        }
    }
}
