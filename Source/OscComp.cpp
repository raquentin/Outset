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
OscComp::OscComp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

OscComp::~OscComp()
{
}

void OscComp::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::palevioletred);

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(juce::Colours::black);
    g.setFont(juce::FontOptions(14.0f));
    g.drawText("Oscillators", getLocalBounds(), juce::Justification::centred, true);
}

void OscComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
