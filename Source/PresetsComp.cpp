/*
  ==============================================================================

    PresetsComp.cpp
    Created: 2 Feb 2025 12:37:21pm
    Author:  josep

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PresetsComp.h"

//==============================================================================
PresetsComp::PresetsComp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

PresetsComp::~PresetsComp()
{
}

void PresetsComp::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);

    g.setColour (juce::Colours::black);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("Presets", getLocalBounds(), juce::Justification::centred, true);
}

void PresetsComp::resized()
{
    

}
