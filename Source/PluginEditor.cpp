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

    setupFrequencyKnob (hiPassFilterSlider,
                        processor.hiPassFrequency,
                        processor.hiPassFrequency,
                        250,
                        0.1);

    setupFrequencyKnob (loPassFilterSlider,
                        processor.loPassFrequency,
                        500,
                        processor.loPassFrequency,
                        0.1);

    setupBypassToggle (hiPassFilterBypassToggle, processor.hiPassBypassed);
    setupBypassToggle (loPassFilterBypassToggle, processor.loPassBypassed);
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
    knobBox.flexDirection = FlexBox::Direction::row;
    knobBox.items.add (FlexItem (hiPassFilterSlider).withFlex (1));
    knobBox.items.add (FlexItem (loPassFilterSlider).withFlex (1));
    knobBox.performLayout (getLocalBounds().removeFromTop (getHeight() / 2).toFloat());

    bypassBox.flexDirection = FlexBox::Direction::row;
    bypassBox.items.add (FlexItem (hiPassFilterBypassToggle).withFlex (1));
    bypassBox.items.add (FlexItem (loPassFilterBypassToggle).withFlex (1));
    bypassBox.performLayout(getLocalBounds().removeFromBottom (getHeight() / 2).toFloat());

    Rectangle<int> rect = getBounds();
    Logger::writeToLog(String (rect.getAspectRatio()));
}

void SimplEqAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &hiPassFilterSlider)
        processor.hiPassFrequency = hiPassFilterSlider.getValue();

    else if (slider == &loPassFilterSlider)
        processor.loPassFrequency = loPassFilterSlider.getValue();
}

void SimplEqAudioProcessorEditor::buttonClicked (Button* button)
{
    if (button == &hiPassFilterBypassToggle)
        processor.hiPassBypassed = hiPassFilterBypassToggle.getToggleState();

    else if (button == &loPassFilterBypassToggle)
        processor.loPassBypassed = loPassFilterBypassToggle.getToggleState();
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
    slider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle (Slider::TextEntryBoxPosition::TextBoxBelow,
                            false, slider.getWidth() * 0.25, 25);
    slider.setMouseDragSensitivity (300);
    slider.addListener (this);

    addAndMakeVisible (slider);
}

void SimplEqAudioProcessorEditor::setupBypassToggle (ToggleButton& toggle, const bool& initialState)
{
    toggle.setToggleState (initialState, NotificationType::dontSendNotification);
    toggle.addListener (this);
    
    addAndMakeVisible (toggle);
}
