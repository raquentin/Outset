/*
  ==============================================================================

    EnvComp.cpp
    Created: 2 Feb 2025 12:46:52pm
    Author:  josep

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvComp.h"

//==============================================================================
EnvComp::EnvComp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

EnvComp::~EnvComp()
{
}

void EnvComp::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgreen);

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(juce::Colours::black);
    g.setFont(juce::FontOptions(14.0f));
    g.drawText("Envelopes", getLocalBounds(), juce::Justification::centred, true);
}

void EnvComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
