/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimplEqAudioProcessorEditor  : public AudioProcessorEditor,
                                     private Slider::Listener,
                                     private ToggleButton::Listener
{
public:
    SimplEqAudioProcessorEditor (SimplEqAudioProcessor&);
    ~SimplEqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged (Slider* slider) override;
    void buttonClicked (Button* button) override;

private:
    void setupFrequencyKnob (Slider& slider,
                             const double& initialValue,
                             const double& startRange,
                             const double& endRange,
                             const double& increment);
    
    void setupBypassToggle (TextButton& textButton,
                            const bool& initialState);

    void setToggleState (Button* button);
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimplEqAudioProcessor& processor;

    Slider hiPassFilterSlider;
    Slider loPassFilterSlider;

    TextButton hiPassFilterBypassToggle;
    TextButton loPassFilterBypassToggle;

    FlexBox knobBox;
    FlexBox bypassBox;
    FlexBox mainBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimplEqAudioProcessorEditor)
};
