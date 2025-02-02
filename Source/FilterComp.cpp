/*
  ==============================================================================

    FilterComp.cpp
    Created: 2 Feb 2025 12:46:44pm
    Author:  josep

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComp.h"

//==============================================================================
FilterComp::FilterComp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FilterComp::~FilterComp()
{
}

void FilterComp::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::orange);

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(juce::Colours::black);
    g.setFont(juce::FontOptions(14.0f));
    g.drawText("Filters", getLocalBounds(), juce::Justification::centred, true);
}

void FilterComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
