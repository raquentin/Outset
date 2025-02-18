/*
  ==============================================================================

    FMBoxComp.cpp
    Created: 13 Feb 2025 2:39:50pm
    Author:  josep

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FMBoxComp.h"

//==============================================================================
FMBoxComp::FMBoxComp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FMBoxComp::~FMBoxComp()
{
}

void FMBoxComp::paint(juce::Graphics& g)
{
    juce::Rectangle<int> bounds = getLocalBounds();

    // fills in outer stuff
    g.fillAll(juce::Colours::lightgrey);

    g.setColour(juce::Colours::black);
    g.drawRect(bounds, 1);

    // We can probably create a list of functions to call based on which algorithm is chosen
    algorithm_1(g, bounds);
}

void FMBoxComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FMBoxComp::algorithm_1(juce::Graphics& g, juce::Rectangle<int> bounds) {
    
    g.setColour(juce::Colours::black);
    g.setFont(juce::FontOptions(14.0f));
    g.drawText("algorithm_1", bounds, juce::Justification::centred, true);
}