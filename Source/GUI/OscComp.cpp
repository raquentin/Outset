/*
  ==============================================================================

    OscComp.cpp
    Created: 2 Feb 2025 12:46:33pm
    Author:  josep

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComp.h"

//==============================================================================
OscComp::OscComp(int tabDepth)
    : juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop)
{
    setTabBarDepth(tabDepth);
    addTab("Osc A", defaultTabColor, new OscTab("Osc A"), true);
    addTab("Osc B", defaultTabColor, new OscTab("Osc B"), true);
    addTab("Osc C", defaultTabColor, new OscTab("Osc C"), true);
    addTab("Osc D", defaultTabColor, new OscTab("Osc D"), true);
}

OscComp::~OscComp()
{
    // Any cleanup if necessary goes here
}
