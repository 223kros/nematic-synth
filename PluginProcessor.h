#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <atomic>
#include <array>
#include <memory>
#include "Params.h"
#include "Presets.h"
#include "SynthEngine.h"
#include "GranularSources.h"

// Colores editables de la interfaz (tonos 0..1). Se guardan dentro del proyecto de FL Studio.
struct ThemeSettings
{
    float hueA = 0.76f;   // acento principal (violeta)
    float hueB = 0.60f;   // acento secundario (azul)
    float hueC = 0.89f;   // acento de brillo (rosa)
    float hueBg = 0.74f;  // fondo
    int preset = 0;
};

class NematicProcessor : public juce::AudioProcessor
{
public:
    NematicProcessor();
    ~NematicProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Vault"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 8.0; }

    int getNumPrograms() override { return (int) presets().size(); }
    int getCurrentProgram() override { return currentProgram.load(); }
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // ---- seccion granular ----
    bool loadUserSample (const juce::File& file);            // carga un archivo de audio como fuente 8 ("TU SAMPLE")
    juce::String getUserSampleName() const;
    std::shared_ptr<const SampleData> getSampleForDisplay (int idx) const;

    // ---- tema de colores ----
    ThemeSettings getTheme() const;
    void setTheme (const ThemeSettings&);

    juce::AudioProcessorValueTreeState apvts;

    static constexpr int kScopeSize = 512;
    std::array<std::atomic<float>, kScopeSize> scope;
    std::atomic<int> scopePos { 0 };

private:
    class Builder;
    friend class Builder;

    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    void applyPreset (int index);
    void installBuiltIn (int idx, std::shared_ptr<SampleData> s);

    NematicEngine engine;
    std::atomic<int> currentProgram { 0 };
    std::array<std::atomic<float>*, P_COUNT> raw {};
    int scopeCounter = 0;

    mutable juce::SpinLock sampleLock;
    std::array<std::shared_ptr<SampleData>, granular_sources::kBuiltIn> builtIn;
    std::shared_ptr<SampleData> userSample;
    std::unique_ptr<Builder> builder;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NematicProcessor)
};
