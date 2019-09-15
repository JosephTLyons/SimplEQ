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
    setSize (500, 250);
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
//    g.setColour (Colours::white);
//    g.drawLine (0, getHeight() / 2, getWidth(), getHeight() / 2);
}

void SimplEqAudioProcessorEditor::resized()
{
    knobBox.flexDirection = FlexBox::Direction::row;
    knobBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    knobBox.alignContent = FlexBox::AlignContent::center;
    knobBox.items.add (FlexItem (hiPassFilterSlider)
                       .withMinHeight ((getHeight() / 2) * 0.90)
                       .withMaxHeight (getHeight() / 2)
                       .withMinWidth (100)
                       .withFlex (1));
    knobBox.items.add (FlexItem (loPassFilterSlider)
                       .withMinHeight ((getHeight() / 2) * 0.90)
                       .withMaxHeight (getHeight() / 2)
                       .withMinWidth (100)
                       .withFlex (1));

    bypassBox.flexDirection = FlexBox::Direction::row;
    bypassBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    bypassBox.alignContent = FlexBox::AlignContent::center;
    bypassBox.items.add (FlexItem (hiPassFilterBypassToggle)
                         .withMinWidth (30)
                         .withMaxWidth (100)
                         .withMinHeight (30)
                         .withFlex (1));
    bypassBox.items.add (FlexItem (loPassFilterBypassToggle)
                         .withMinWidth (30)
                         .withMaxWidth (100)
                         .withMinHeight (30)
                         .withFlex (1));

    mainBox.flexDirection = FlexBox::Direction::column;
    mainBox.items.add (FlexItem (knobBox).withFlex (0.5).withMargin ({70, 0, 0, 0}));
    mainBox.items.add (FlexItem (bypassBox).withFlex (0.5).withMargin ({35, 0, 0, 0}));
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
//    slider.setSkewFactorFromMidPoint((slider.getMinimum() + slider.getMaximum()) / 2);

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
