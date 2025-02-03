/*
  ==============================================================================

    PresetsComp.h
    Created: 2 Feb 2025 12:37:21pm
    Author:  josep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PresetsComp  : public juce::Component
{
public:
    PresetsComp();
    ~PresetsComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsComp)
};
