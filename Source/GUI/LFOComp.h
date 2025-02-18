/*
  ==============================================================================

    LFOComp.h
    Created: 2 Feb 2025 12:49:27pm
    Author:  josep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FMBoxComp.h"

//==============================================================================
/*
*/
class LFOComp  : public juce::Component
{
public:
    LFOComp();
    ~LFOComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    FMBoxComp fm_box;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComp)
};
