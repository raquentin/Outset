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

        addTab("Osc 1", oscColor, new OscEnvParent("Osc 1"), true);
        addTab("Osc 2", oscColor, new OscEnvParent("Osc 2"), true);
        addTab("Osc 3", oscColor, new OscEnvParent("Osc 3"), true);
        addTab("Osc 4", oscColor, new OscEnvParent("Osc 4"), true);
        addTab("Osc 5", oscColor, new OscEnvParent("Osc 5"), true);
        addTab("Osc 6", oscColor, new OscEnvParent("Osc 6"), true);
    }

    ~OscEnvTab() override = default;
};


