/*
  ==============================================================================

    EnvComp.h
    Created: 2 Feb 2025 12:46:52pm
    Author:  josep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EnvComp  : public juce::Component
{
public:
    EnvComp();
    ~EnvComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvComp)
};
