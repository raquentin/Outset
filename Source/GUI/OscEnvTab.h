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


// This component acts as the parent for the OscEnvParents. Switching tabs makes one of the 6 OscEnv Parents Visible.
class OscEnvTab : public juce::TabbedComponent
{
public:
    OscEnvTab(juce::AudioProcessorValueTreeState& apvtsRef)
        : juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop)
    {
        juce::Colour oscColor = juce::Colours::palevioletred;
        setTabBarDepth(30);

        addTab("Osc 1", oscColor, new OscEnvParent(1, apvtsRef), true);
        addTab("Osc 2", oscColor, new OscEnvParent(2, apvtsRef), true);
        addTab("Osc 3", oscColor, new OscEnvParent(3, apvtsRef), true);
        addTab("Osc 4", oscColor, new OscEnvParent(4, apvtsRef), true);
        addTab("Osc 5", oscColor, new OscEnvParent(5, apvtsRef), true);
        addTab("Osc 6", oscColor, new OscEnvParent(6, apvtsRef), true);
    }

    ~OscEnvTab() override = default;
};


