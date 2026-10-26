#include "PluginEditor.h"

using namespace juce;

// ----------------------------------------------------------------------------
//  Look & feel neon
// ----------------------------------------------------------------------------
void NeonLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int w, int h, float pos,
                                        float startAngle, float endAngle, Slider&)
{
    auto b = Rectangle<float> ((float) x, (float) y, (float) w, (float) h).reduced (8.f);
    const float r = jmin (b.getWidth(), b.getHeight()) * 0.5f;
    const auto c = b.getCentre();
    const float angle = startAngle + pos * (endAngle - startAngle);
    const float arcR = r - 2.f;

    Path track;
    track.addCentredArc (c.x, c.y, arcR, arcR, 0.f, startAngle, endAngle, true);
    g.setColour (Colour (0x22ffffff));
    g.strokePath (track, PathStrokeType (3.f, PathStrokeType::curved, PathStrokeType::rounded));

    Path val;
    val.addCentredArc (c.x, c.y, arcR, arcR, 0.f, startAngle, jmax (startAngle + 0.001f, angle), true);

    for (int k = 4; k >= 1; --k)
    {
        g.setColour (neon::violet.withAlpha (0.07f));
        g.strokePath (val, PathStrokeType (3.f + (float) k * 3.f, PathStrokeType::curved, PathStrokeType::rounded));
    }
    g.setGradientFill (ColourGradient (neon::cyan, c.x - r, c.y + r, neon::pink, c.x + r, c.y - r, false));
    g.strokePath (val, PathStrokeType (3.4f, PathStrokeType::curved, PathStrokeType::rounded));

    // cuerpo
    const float br = arcR - 8.f;
    g.setGradientFill (ColourGradient (Colour (0xff2a1458), c.x, c.y - br, Colour (0xff0d0620), c.x, c.y + br, false));
    g.fillEllipse (c.x - br, c.y - br, br * 2.f, br * 2.f);
    g.setColour (neon::violet.withAlpha (0.55f));
    g.drawEllipse (c.x - br, c.y - br, br * 2.f, br * 2.f, 1.2f);

    // aguja
    const float px1 = c.x + std::sin (angle) * br * 0.35f, py1 = c.y - std::cos (angle) * br * 0.35f;
    const float px2 = c.x + std::sin (angle) * br * 0.9f,  py2 = c.y - std::cos (angle) * br * 0.9f;
    g.setColour (neon::pink.withAlpha (0.25f));
    g.drawLine (px1, py1, px2, py2, 5.f);
    g.setColour (Colours::white);
    g.drawLine (px1, py1, px2, py2, 2.2f);
}

void NeonLookAndFeel::drawButtonBackground (Graphics& g, Button& btn, const Colour&, bool highlighted, bool down)
{
    auto b = btn.getLocalBounds().toFloat().reduced (2.f);
    const bool on = btn.getToggleState();
    const auto col = btn.findColour (TextButton::buttonColourId);

    if (on)
    {
        for (int k = 3; k >= 1; --k)
        {
            g.setColour (col.withAlpha (0.08f));
            g.drawRoundedRectangle (b.expanded ((float) k * 1.5f), 9.f, 2.f);
        }
        g.setColour (col.withAlpha (0.20f));
        g.fillRoundedRectangle (b, 9.f);
    }
    else if (highlighted || down)
    {
        g.setColour (col.withAlpha (0.10f));
        g.fillRoundedRectangle (b, 9.f);
    }
    g.setColour (on ? col : col.withAlpha (highlighted ? 0.8f : 0.45f));
    g.drawRoundedRectangle (b, 9.f, on ? 2.f : 1.2f);
}

Font NeonLookAndFeel::getTextButtonFont (TextButton&, int buttonHeight)
{
    return Font (FontOptions ((float) jmin (16, (int) (buttonHeight * 0.45f)) + 1.f, Font::bold));
}

// ----------------------------------------------------------------------------
//  Editor
// ----------------------------------------------------------------------------
void NematicEditor::glowText (Graphics& g, const String& text, Rectangle<int> r, Colour col, float size, Justification just)
{
    g.setFont (Font (FontOptions (size, Font::bold)));
    for (int k = 3; k >= 1; --k)
    {
        g.setColour (col.withAlpha (0.07f));
        for (int dx = -k; dx <= k; dx += k)
            for (int dy = -k; dy <= k; dy += k)
                g.drawText (text, r.translated (dx, dy), just);
    }
    g.setColour (col.brighter (0.3f));
    g.drawText (text, r, just);
}

NematicEditor::NematicEditor (NematicProcessor& p) : AudioProcessorEditor (&p), proc (p)
{
    setLookAndFeel (&laf);
    setSize (960, 640);

    const char* secNames[2] = { "ATMOSFERA", "ROMANTICO" };
    for (int i = 0; i < 2; ++i)
    {
        secBtn[i].setButtonText (secNames[i]);
        secBtn[i].setColour (TextButton::buttonColourId, i == 0 ? neon::cyan : neon::pink);
        secBtn[i].setColour (TextButton::textColourOffId, Colours::white.withAlpha (0.75f));
        secBtn[i].setColour (TextButton::textColourOnId, Colours::white);
        secBtn[i].onClick = [this, i]
        {
            if (section == i) return;
            section = i;
            cat = {};
            rebuildCategories();
            // cargar el primer preset de la categoria
            if (! chipIndex.empty()) loadProgram (chipIndex.front());
        };
        addAndMakeVisible (secBtn[i]);
    }

    for (auto* b : { &prevBtn, &nextBtn })
    {
        b->setColour (TextButton::buttonColourId, neon::violet);
        b->setColour (TextButton::textColourOffId, Colours::white);
        addAndMakeVisible (b);
    }
    prevBtn.onClick = [this] { const int n = proc.getNumPrograms(); loadProgram ((proc.getCurrentProgram() + n - 1) % n); };
    nextBtn.onClick = [this] { const int n = proc.getNumPrograms(); loadProgram ((proc.getCurrentProgram() + 1) % n); };

    struct K { int idx; const char* label; };
    const K ks[10] = { { P_CUTOFF, "BRILLO" }, { P_RESO, "RESO" }, { P_AA, "ATAQUE" }, { P_AR, "RELEASE" }, { P_DET, "DETUNE" },
                       { P_DRIVE, "DRIVE" }, { P_CHORUS, "CHORUS" }, { P_DMIX, "DELAY" }, { P_VMIX, "REVERB" }, { P_VOL, "VOLUMEN" } };
    for (size_t i = 0; i < knobs.size(); ++i)
    {
        auto& k = knobs[i];
        k.label = ks[i].label;
        k.slider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
        k.slider.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        k.slider.setRotaryParameters (MathConstants<float>::pi * 1.2f, MathConstants<float>::pi * 2.8f, true);
        k.slider.setPopupDisplayEnabled (true, true, this);
        addAndMakeVisible (k.slider);
        k.attach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (proc.apvts, paramDefs()[(size_t) ks[i].idx].id, k.slider);
    }

    syncFromProgram();
    startTimerHz (30);
}

NematicEditor::~NematicEditor()
{
    stopTimer();
    setLookAndFeel (nullptr);
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
    const auto& pr = list[(size_t) cur];

    if (pr.section != section || cat != pr.cat || catBtns.isEmpty())
    {
        section = pr.section;
        cat = pr.cat;
        rebuildCategories();
    }
    shownProgram = cur;
    refreshStates();
    repaint();
}

void NematicEditor::rebuildCategories()
{
    catBtns.clear();
    const auto cats = categoriesFor (section);
    if (cat.isEmpty() || ! cats.contains (cat)) cat = cats[0];

    for (auto& c : cats)
    {
        auto* b = catBtns.add (new TextButton (c));
        b->setColour (TextButton::buttonColourId, sectionColour());
        b->setColour (TextButton::textColourOffId, Colours::white.withAlpha (0.7f));
        b->setColour (TextButton::textColourOnId, Colours::white);
        b->onClick = [this, c]
        {
            cat = c;
            rebuildChips();
            if (! chipIndex.empty()) loadProgram (chipIndex.front());
        };
        addAndMakeVisible (b);
    }
    rebuildChips();
    resized();
}

void NematicEditor::rebuildChips()
{
    chipBtns.clear();
    chipIndex.clear();
    const auto& list = presets();
    for (int i = 0; i < (int) list.size(); ++i)
    {
        if (list[(size_t) i].section != section || cat != list[(size_t) i].cat) continue;
        auto* b = chipBtns.add (new TextButton (list[(size_t) i].name));
        chipIndex.push_back (i);
        b->setColour (TextButton::buttonColourId, section == 0 ? neon::violet : neon::pink);
        b->setColour (TextButton::textColourOffId, Colours::white.withAlpha (0.8f));
        b->setColour (TextButton::textColourOnId, Colours::white);
        b->onClick = [this, i] { loadProgram (i); };
        addAndMakeVisible (b);
    }
    resized();
}

void NematicEditor::refreshStates()
{
    for (int i = 0; i < 2; ++i) secBtn[i].setToggleState (section == i, dontSendNotification);
    for (auto* b : catBtns) b->setToggleState (b->getButtonText() == cat, dontSendNotification);
    for (int i = 0; i < chipBtns.size(); ++i)
        chipBtns[i]->setToggleState (chipIndex[(size_t) i] == proc.getCurrentProgram(), dontSendNotification);
}

void NematicEditor::timerCallback()
{
    if (proc.getCurrentProgram() != shownProgram) syncFromProgram();
    repaint (scopeRect);
}

void NematicEditor::resized()
{
    const int W = getWidth();
    secBtn[0].setBounds (28, 92, (W - 56 - 20) / 2, 46);
    secBtn[1].setBounds (28 + (W - 56 - 20) / 2 + 20, 92, (W - 56 - 20) / 2, 46);

    prevBtn.setBounds (W - 400, 24, 40, 34);
    nameRect = { W - 356, 22, 270, 38 };
    nextBtn.setBounds (W - 78, 24, 40, 34);

    int x = 28;
    for (auto* b : catBtns) { b->setBounds (x, 152, 100, 32); x += 108; }

    const int chipW = 142, gap = 8;
    int cx = 28, cy = 196;
    for (auto* b : chipBtns)
    {
        if (cx + chipW > W - 20) { cx = 28; cy += 40; }
        b->setBounds (cx, cy, chipW, 34);
        cx += chipW + gap;
    }

    scopeRect = { 28, 262, W - 56, 150 };

    const int kw = (W - 56) / 10;
    for (size_t i = 0; i < knobs.size(); ++i)
    {
        const int kx = 28 + (int) i * kw;
        knobs[i].slider.setBounds (kx + 4, 440, kw - 8, kw - 8);
        knobs[i].labelRect = { kx, 440 + kw - 6, kw, 20 };
    }
}

void NematicEditor::paint (Graphics& g)
{
    const int W = getWidth(), H = getHeight();

    g.setGradientFill (ColourGradient (Colour (0xff070315), 0.f, 0.f, Colour (0xff22094a), 0.f, (float) H, false));
    g.fillAll();

    // estrellas
    Random rnd (7);
    for (int i = 0; i < 70; ++i)
    {
        const float sx = rnd.nextFloat() * W, sy = rnd.nextFloat() * 250.f, a = 0.1f + rnd.nextFloat() * 0.35f;
        g.setColour (Colours::white.withAlpha (a));
        g.fillEllipse (sx, sy, 1.6f, 1.6f);
    }

    // grilla synthwave al fondo
    const float horizon = 420.f;
    for (int k = 1; k <= 10; ++k)
    {
        const float t = (float) k / 10.f;
        const float yy = horizon + t * t * ((float) H - horizon);
        g.setColour (neon::violet.withAlpha (0.06f + 0.10f * t));
        g.drawHorizontalLine ((int) yy, 0.f, (float) W);
    }
    for (int i = -24; i <= 24; ++i)
    {
        g.setColour (neon::pink.withAlpha (0.10f));
        g.drawLine (W * 0.5f + (float) i * 14.f, horizon, W * 0.5f + (float) i * 70.f, (float) H, 1.f);
    }

    // header
    glowText (g, "NEMATIC", { 28, 12, 300, 52 }, neon::violet, 40.f);
    g.setColour (Colours::white.withAlpha (0.55f));
    g.setFont (Font (FontOptions (13.f, Font::bold)));
    g.drawText ("S O U N D   L A B", 32, 60, 300, 18, Justification::centredLeft);

    // nombre del preset
    g.setColour (Colour (0x55000000));
    g.fillRoundedRectangle (nameRect.toFloat(), 9.f);
    g.setColour (sectionColour().withAlpha (0.7f));
    g.drawRoundedRectangle (nameRect.toFloat(), 9.f, 1.4f);
    glowText (g, proc.getNumPrograms() > 0 ? String (presets()[(size_t) jlimit (0, proc.getNumPrograms() - 1, proc.getCurrentProgram())].name) : String(),
              nameRect, sectionColour(), 17.f, Justification::centred);

    // osciloscopio
    auto sr = scopeRect.toFloat();
    g.setColour (Colour (0x66050212));
    g.fillRoundedRectangle (sr, 12.f);
    g.setGradientFill (ColourGradient (neon::violet, sr.getX(), sr.getY(), neon::cyan, sr.getRight(), sr.getBottom(), false));
    g.drawRoundedRectangle (sr, 12.f, 1.5f);

    g.setColour (Colours::white.withAlpha (0.06f));
    g.drawHorizontalLine ((int) sr.getCentreY(), sr.getX() + 8.f, sr.getRight() - 8.f);

    Path wavePath;
    const int pos = proc.scopePos.load();
    const float amp = sr.getHeight() * 0.42f;
    for (int i = 0; i < NematicProcessor::kScopeSize; ++i)
    {
        const float s = proc.scope[(size_t) ((pos + i) % NematicProcessor::kScopeSize)].load();
        const float px = sr.getX() + 8.f + (sr.getWidth() - 16.f) * (float) i / (float) (NematicProcessor::kScopeSize - 1);
        const float py = sr.getCentreY() - jlimit (-1.f, 1.f, s * 1.6f) * amp;
        if (i == 0) wavePath.startNewSubPath (px, py); else wavePath.lineTo (px, py);
    }
    for (int k = 3; k >= 1; --k)
    {
        g.setColour (neon::pink.withAlpha (0.10f));
        g.strokePath (wavePath, PathStrokeType (2.f + (float) k * 3.f, PathStrokeType::curved, PathStrokeType::rounded));
    }
    g.setGradientFill (ColourGradient (neon::cyan, sr.getX(), 0.f, neon::pink, sr.getRight(), 0.f, false));
    g.strokePath (wavePath, PathStrokeType (2.f, PathStrokeType::curved, PathStrokeType::rounded));

    // etiquetas de los knobs
    g.setFont (Font (FontOptions (12.5f, Font::bold)));
    g.setColour (Colours::white.withAlpha (0.8f));
    for (auto& k : knobs)
        g.drawText (k.label, k.labelRect, Justification::centred);

    g.setColour (Colours::white.withAlpha (0.3f));
    g.setFont (Font (FontOptions (11.f)));
    g.drawText ("Nematic  -  Tocá notas MIDI para escuchar el preset", 28, H - 26, W - 56, 16, Justification::centred);
}
