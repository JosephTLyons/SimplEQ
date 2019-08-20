/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimplEqAudioProcessorEditor::SimplEqAudioProcessorEditor (SimplEqAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (800, 200);
    setResizable (true, true);

    setupFrequencyKnob (highPassFilterSlider,
                        processor.highPassFrequency,
                        processor.highPassFrequency,
                        250,
                        0.1);

    setupFrequencyKnob (lowPassFilterSlider,
                        processor.lowPassFrequency,
                        500,
                        processor.lowPassFrequency,
                        0.1);
}

SimplEqAudioProcessorEditor::~SimplEqAudioProcessorEditor()
{
}

//==============================================================================
void SimplEqAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void SimplEqAudioProcessorEditor::resized()
{
    //==============================================================================
    knobBox.flexDirection = FlexBox::Direction::row;
    knobBox.items.add (FlexItem (highPassFilterSlider).withFlex (1));
    knobBox.items.add (FlexItem (lowPassFilterSlider).withFlex (1));

    float heightAdjustment = getHeight() * (3.0f / 8.0f);

    Rectangle<float> knobBoxFrame = getLocalBounds()
                                        .removeFromBottom (heightAdjustment)
                                        .removeFromTop (heightAdjustment)
                                        .toFloat();

    knobBox.performLayout (knobBoxFrame);
}

void SimplEqAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &highPassFilterSlider)
        processor.highPassFrequency = highPassFilterSlider.getValue();

    else if (slider == &lowPassFilterSlider)
        processor.lowPassFrequency = lowPassFilterSlider.getValue();
}

void SimplEqAudioProcessorEditor::setupFrequencyKnob (Slider& slider,
                                                      const double& initialValue,
                                                      const double& startRange,
                                                      const double& endRange,
                                                      const double& increment)
{
    slider.setRange (startRange, endRange, increment);
    slider.setValue (initialValue);
    slider.setTextValueSuffix (" Hz");
    slider.setPopupDisplayEnabled (false, false, this);
    slider.setSliderStyle  (Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow,
                            false, slider.getWidth() * 0.5, 25);
    slider.setMouseDragSensitivity (50);
    slider.setVelocityBasedMode (true);

    slider.addListener (this);

    addAndMakeVisible (slider);
}
