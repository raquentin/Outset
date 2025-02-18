/*
  ==============================================================================

    LFOComp.cpp
    Created: 2 Feb 2025 12:49:27pm
    Author:  josep

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOComp.h"

//==============================================================================
LFOComp::LFOComp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(fm_box);
}

LFOComp::~LFOComp()
{
}

void LFOComp::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::skyblue);

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(juce::Colours::black);
    g.setFont(juce::FontOptions(14.0f));
    g.drawText("LFO/FM", getLocalBounds(), juce::Justification::centred, true);
}

void LFOComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> bounds = getLocalBounds();

    int x = (bounds.getWidth() / 2) - bounds.getHeight() / 4;
    int y = bounds.getHeight() / 4;
    juce::Rectangle<int> centeredRect(x, y, bounds.getHeight() / 2, bounds.getHeight() / 2);

    fm_box.setBounds(centeredRect);
}
