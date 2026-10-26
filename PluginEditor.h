#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

namespace neon
{
    const juce::Colour violet { 0xffb14aff }, pink { 0xffff4fd8 }, cyan { 0xff4df3ff }, blue { 0xff5b7bff };
}

class NeonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider (juce::Graphics&, int x, int y, int w, int h, float pos,
                           float startAngle, float endAngle, juce::Slider&) override;
    void drawButtonBackground (juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool) override;
    juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override;
};

class NematicEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit NematicEditor (NematicProcessor&);
    ~NematicEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    struct Knob
    {
        juce::Slider slider;
        juce::String label;
        juce::Rectangle<int> labelRect;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attach;
    };

    void timerCallback() override;
    void rebuildCategories();
    void rebuildChips();
    void refreshStates();
    void syncFromProgram();
    void loadProgram (int index);
    juce::Colour sectionColour() const { return section == 0 ? neon::cyan : neon::pink; }
    static void glowText (juce::Graphics&, const juce::String&, juce::Rectangle<int>, juce::Colour, float size,
                          juce::Justification just = juce::Justification::centredLeft);

    NematicProcessor& proc;
    NeonLookAndFeel laf;

    int section = 0;
    juce::String cat;
    int shownProgram = -1;

    juce::TextButton secBtn[2];
    juce::TextButton prevBtn { "<" }, nextBtn { ">" };
    juce::OwnedArray<juce::TextButton> catBtns, chipBtns;
    std::vector<int> chipIndex;
    std::array<Knob, 10> knobs;

    juce::Rectangle<int> scopeRect, nameRect;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NematicEditor)
};
