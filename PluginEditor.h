#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

// Paleta de la interfaz, calculada a partir de los 4 tonos editables.
struct Palette
{
    juce::Colour bg1, bg2, accA, accB, accC;
    static Palette from (const ThemeSettings& t);
};

class CleanLookAndFeel : public juce::LookAndFeel_V4
{
public:
    Palette pal;

    void drawRotarySlider (juce::Graphics&, int x, int y, int w, int h, float pos,
                           float startAngle, float endAngle, juce::Slider&) override;
    void drawLinearSlider (juce::Graphics&, int x, int y, int w, int h, float sliderPos,
                           float minPos, float maxPos, juce::Slider::SliderStyle, juce::Slider&) override;
    void drawButtonBackground (juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool) override;
    juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override;
};

class NematicEditor : public juce::AudioProcessorEditor,
                      public juce::FileDragAndDropTarget,
                      private juce::ListBoxModel,
                      private juce::Timer
{
public:
    explicit NematicEditor (NematicProcessor&);
    ~NematicEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag (const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;

private:
    struct Knob
    {
        juce::Slider slider;
        juce::String label;
        juce::Rectangle<int> labelRect;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attach;
    };

    // ListBoxModel
    int getNumRows() override { return (int) rows.size(); }
    void paintListBoxItem (int row, juce::Graphics&, int w, int h, bool selected) override;
    void listBoxItemClicked (int row, const juce::MouseEvent&) override;

    void timerCallback() override;

    Knob* addKnob (juce::OwnedArray<Knob>& arr, int paramIdx, const char* label);
    void rebuildCategories();
    void rebuildRows();
    void refreshStates();
    void syncFromProgram();
    void loadProgram (int index);
    void applyTheme (bool save);
    void refreshColours();
    void chooseSampleFile();
    void loadSampleFile (const juce::File&);
    void setSourceIndex (int idx);
    void rebuildPeaks();
    juce::Colour sectionColour (int s) const;
    static void drawPanel (juce::Graphics&, juce::Rectangle<int>, juce::Colour edge);

    NematicProcessor& proc;
    CleanLookAndFeel laf;
    ThemeSettings theme;

    int section = 0;
    juce::String cat;
    int shownProgram = -1;
    bool searching = false;

    juce::TextButton secBtn[kNumSections];
    juce::TextButton prevBtn { "<" }, nextBtn { ">" };
    juce::OwnedArray<juce::TextButton> catBtns;
    juce::TextEditor search;
    juce::ListBox presetList { "presets", nullptr };
    std::vector<int> rows;

    juce::OwnedArray<Knob> soundKnobs, granKnobs;

    // colores
    juce::TextButton themeBtn[4];
    juce::Slider hueSl[4];

    // granular
    juce::ComboBox srcBox;
    juce::TextButton loadBtn { "CARGAR SAMPLE" };
    juce::TextButton keyBtn { "KEY" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> keyAttach;
    std::unique_ptr<juce::FileChooser> chooser;
    std::shared_ptr<const SampleData> shownSample;
    int shownSrc = -1;
    juce::String shownUserName;
    static constexpr int kPeakCols = 380;
    std::vector<float> peaks;
    std::atomic<float>* rawSrc = nullptr;
    std::atomic<float>* rawPos = nullptr;
    std::atomic<float>* rawPosR = nullptr;

    juce::Rectangle<int> scopeRect, nameRect, waveRect;
    juce::Rectangle<int> panelLeft, panelColors, panelSound, panelGran;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NematicEditor)
};
