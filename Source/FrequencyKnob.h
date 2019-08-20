/*
  ==============================================================================

    FrequencyKnob.h
    Created: 20 Aug 2019 6:54:49am
    Author:  Joseph Lyons

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginEditor.h"

class FrequencyKnob: public Slider
{
private:
public:
    FrequencyKnob (SimplEqAudioProcessorEditor* editor,
                   const unsigned int& initialValue,
                   const unsigned int& startRange,
                   const unsigned int& endRange,
                   const double& incrementValue);
};
