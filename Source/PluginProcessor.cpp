/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimplEqAudioProcessor::SimplEqAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    hiPassFrequency = 1;
    loPassFrequency = 22000;

    hiPassBypassed = false;
    loPassBypassed = false;
}

SimplEqAudioProcessor::~SimplEqAudioProcessor()
{
}

//==============================================================================
const String SimplEqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimplEqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimplEqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimplEqAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimplEqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimplEqAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimplEqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimplEqAudioProcessor::setCurrentProgram (int index)
{
}

const String SimplEqAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimplEqAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimplEqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SimplEqAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimplEqAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimplEqAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (! hiPassBypassed)
        hiPassFilter (buffer);

    if (! loPassBypassed)
        loPassFilter  (buffer);
}

//==============================================================================
bool SimplEqAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimplEqAudioProcessor::createEditor()
{
    return new SimplEqAudioProcessorEditor (*this);
}

//==============================================================================
void SimplEqAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimplEqAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimplEqAudioProcessor();
}

void SimplEqAudioProcessor::hiPassFilter (AudioBuffer<float>& buffer)
{
    iirFilterHiPassL.setCoefficients (IIRCoefficients::makeHighPass (getSampleRate(), hiPassFrequency));
    iirFilterHiPassR.setCoefficients (IIRCoefficients::makeHighPass (getSampleRate(), hiPassFrequency));

    iirFilterHiPassL.processSamples (buffer.getWritePointer (0), buffer.getNumSamples());
    iirFilterHiPassR.processSamples (buffer.getWritePointer (1), buffer.getNumSamples());
}

void SimplEqAudioProcessor::loPassFilter (AudioBuffer<float>& buffer)
{
    iirFilterLoPassL.setCoefficients (IIRCoefficients::makeLowPass (getSampleRate(), loPassFrequency));
    iirFilterLoPassR.setCoefficients (IIRCoefficients::makeLowPass (getSampleRate(), loPassFrequency));

    iirFilterLoPassL.processSamples (buffer.getWritePointer (0), buffer.getNumSamples());
    iirFilterLoPassR.processSamples (buffer.getWritePointer (1), buffer.getNumSamples());
}
