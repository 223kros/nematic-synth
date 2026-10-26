cmake_minimum_required(VERSION 3.22)
project(NematicSoundLab VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
# runtime estatico: el plugin no necesita instalar Visual C++ Redistributable
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (DEFINED ENV{JUCE_LOCAL_DIR})
    add_subdirectory($ENV{JUCE_LOCAL_DIR} juce)
else()
    include(FetchContent)
    FetchContent_Declare(juce
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 8.0.4
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(juce)
endif()

juce_add_plugin(NematicSoundLab
    COMPANY_NAME "Nematic"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE Nmtc
    PLUGIN_CODE Nsl1
    FORMATS VST3
    PRODUCT_NAME "Nematic Sound Lab"
    VST3_CATEGORIES Instrument Synth)

target_sources(NematicSoundLab PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

target_compile_definitions(NematicSoundLab PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(NematicSoundLab
    PRIVATE
        juce::juce_audio_processors
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags)
