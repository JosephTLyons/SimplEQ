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
    setSize (800, 250);
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

    bypassBox.flexDirection = FlexBox::Direction::row;
    bypassBox.justifyContent = FlexBox::JustifyContent::spaceAround;
//    bypassBox.alignContent = FlexBox::AlignContent::center;
    bypassBox.items.add (FlexItem (hiPassFilterBypassToggle).withMaxWidth (100.0).withMaxHeight (30.0).withFlex (1));
    bypassBox.items.add (FlexItem (loPassFilterBypassToggle).withMaxWidth (100.0).withMaxHeight (30.0).withFlex (1));

    mainBox.flexDirection = FlexBox::Direction::column;
    mainBox.items.add (FlexItem (knobBox).withFlex (0.5));
    mainBox.items.add (FlexItem (bypassBox).withFlex (0.5));
    mainBox.performLayout (getLocalBounds().toFloat());
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
    {
        processor.hiPassBypassed = hiPassFilterBypassToggle.getToggleState();
        setToggleState (button);
    }

    else if (button == &loPassFilterBypassToggle)
    {
        processor.loPassBypassed = loPassFilterBypassToggle.getToggleState();
        setToggleState (button);
    }
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

void SimplEqAudioProcessorEditor::setupBypassToggle (TextButton& textButton,
                                                     const bool& initialState)
{
    textButton.setClickingTogglesState (true);
    textButton.setToggleState (initialState, NotificationType::dontSendNotification);
    setToggleState (&textButton);
    textButton.addListener (this);
    
    addAndMakeVisible (textButton);
}

void SimplEqAudioProcessorEditor::setToggleState (Button* button)
{
    if (button->getToggleState())
        button->setButtonText ("Disabled");

    else
        button->setButtonText ("Enabled");
}
