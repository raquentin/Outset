/*
  ==============================================================================

    OscEnvParent.h
    Created: 4 Feb 2025 2:22:46pm
    Author:  ryanb

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OscComp.h"
#include "EnvComp.h"

class OscEnvParent : public juce::Component
{
public:
    OscEnvParent(const juce::String& title)
        : oscComp(title)
    {
        addAndMakeVisible(oscComp);
        addAndMakeVisible(envComp);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        bounds = bounds.withTrimmedBottom(30);
        auto oscBounds = bounds.removeFromTop(bounds.getHeight() / 2);
        oscComp.setBounds(oscBounds);
        envComp.setBounds(bounds);
    }

private:
    OscComp oscComp;
    EnvComp envComp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscEnvParent)
};


