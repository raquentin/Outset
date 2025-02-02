/*
  ==============================================================================

    OscComp.h
    Created: 2 Feb 2025 12:46:33pm
    Author:  josep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComp  : public juce::Component
{
public:
    OscComp();
    ~OscComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComp)
};
