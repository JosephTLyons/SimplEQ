/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class SimplEqAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SimplEqAudioProcessor();
    ~SimplEqAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    double hiPassFrequency;
    double loPassFrequency;

    bool hiPassBypassed;
    bool loPassBypassed;

private:
    // Private methods
    void hiPassFilter (AudioBuffer<float>& buffer);
    void loPassFilter (AudioBuffer<float>& buffer);
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimplEqAudioProcessor)

    IIRFilter iirFilterHiPassL;
    IIRFilter iirFilterHiPassR;

    IIRFilter iirFilterLoPassL;
    IIRFilter iirFilterLoPassR;
};
