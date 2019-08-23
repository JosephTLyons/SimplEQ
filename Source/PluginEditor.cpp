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

    setupBypassToggle (highPassFilterBypassToggle, processor.highPassBypassed);
    setupBypassToggle (lowPassFilterBypassToggle, processor.lowPassBypassed);
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
    knobBox.performLayout (getLocalBounds().removeFromTop (getHeight() / 2).toFloat());

    bypassBox.flexDirection = FlexBox::Direction::row;
    bypassBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    bypassBox.items.add (FlexItem (highPassFilterBypassToggle).withFlex (1));
    bypassBox.items.add (FlexItem (lowPassFilterBypassToggle).withFlex (1));
    bypassBox.performLayout(getLocalBounds().removeFromBottom (getHeight() / 2).toFloat());
}

void SimplEqAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &highPassFilterSlider)
        processor.highPassFrequency = highPassFilterSlider.getValue();

    else if (slider == &lowPassFilterSlider)
        processor.lowPassFrequency = lowPassFilterSlider.getValue();
}

void SimplEqAudioProcessorEditor::buttonClicked (Button* button)
{
    if (button == &highPassFilterBypassToggle)
        processor.highPassBypassed = highPassFilterBypassToggle.getToggleState();

    else if (button == &lowPassFilterBypassToggle)
        processor.lowPassBypassed = lowPassFilterBypassToggle.getToggleState();
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
                            false, slider.getWidth() * 0.25, 25);
    slider.setMouseDragSensitivity (300);
    slider.addListener (this);

    addAndMakeVisible (slider);
}

void SimplEqAudioProcessorEditor::setupBypassToggle (ToggleButton& toggle,
                                                     const bool& initialState)
{
    toggle.setToggleState (initialState, NotificationType::dontSendNotification);
    toggle.addListener (this);
    
    addAndMakeVisible (toggle);
}
