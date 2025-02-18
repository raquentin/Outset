/*
  ==============================================================================

    OscEnvTab.h
    Created: 4 Feb 2025 2:22:46pm
    Author:  ryanb

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OscEnvParent.h"

class OscEnvTab : public juce::TabbedComponent
{
public:
    OscEnvTab()
        : juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop)
    {
        juce::Colour oscColor = juce::Colours::palevioletred;
        setTabBarDepth(30);

        addTab("Oscillator A", oscColor, new OscEnvParent("Oscillator A"), true);
        addTab("Oscillator B", oscColor, new OscEnvParent("Oscillator B"), true);
        addTab("Oscillator C", oscColor, new OscEnvParent("Oscillator C"), true);
        addTab("Oscillator D", oscColor, new OscEnvParent("Oscillator D"), true);
    }

    ~OscEnvTab() override = default;
};


