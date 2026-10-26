#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <atomic>
#include <array>
#include "Params.h"
#include "Presets.h"
#include "SynthEngine.h"

class NematicProcessor : public juce::AudioProcessor
{
public:
    NematicProcessor();
    ~NematicProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Nematic Sound Lab"; }
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

    juce::AudioProcessorValueTreeState apvts;

    static constexpr int kScopeSize = 512;
    std::array<std::atomic<float>, kScopeSize> scope;
    std::atomic<int> scopePos { 0 };

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    void applyPreset (int index);

    NematicEngine engine;
    std::atomic<int> currentProgram { 0 };
    std::array<std::atomic<float>*, P_COUNT> raw {};
    int scopeCounter = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NematicProcessor)
};
