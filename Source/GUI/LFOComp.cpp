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
    algo_ind = 0;

    juce::Path next_trianglePath, prev_trianglePath;
    next_trianglePath.addTriangle(0, 0, 30, 15, 0, 30);
    prev_trianglePath.addTriangle(30, 0, 0, 15, 30, 30);

    auto drawable = std::make_unique<juce::DrawablePath>();
    drawable->setPath(next_trianglePath);
    drawable->setFill(juce::Colours::white);

    next_b = std::make_unique<juce::DrawableButton>("next", juce::DrawableButton::ImageFitted);
    next_b->setImages(drawable.get());
    addAndMakeVisible(next_b.get());

    drawable->setPath(prev_trianglePath);

    prev_b = std::make_unique<juce::DrawableButton>("prev", juce::DrawableButton::ImageFitted);
    prev_b->setImages(drawable.get());
    addAndMakeVisible(prev_b.get());


    // Attach button click logic
    next_b->onClick = [this]() {
        algo_ind = (algo_ind + 1) % 32;
        repaint();
    };

    prev_b->onClick = [this]() {
        algo_ind--;
        if (algo_ind == -1) algo_ind = 31;
        repaint();
    };
}

LFOComp::~LFOComp()
{
}

void LFOComp::paint (juce::Graphics& g)
{
    juce::Rectangle<int> bounds = getLocalBounds();
    g.fillAll(juce::Colours::skyblue);

    g.setColour(juce::Colours::black);
    g.drawRect(bounds, 1);

    g.setColour(juce::Colours::black);
    g.setFont(juce::FontOptions(14.0f));

    int x = (bounds.getWidth() / 2) - bounds.getHeight() / 3;
    int y = bounds.getHeight() / 5;
    juce::Rectangle<int> centeredRect(x, y, bounds.getHeight() / 3 * 2, bounds.getHeight() / 3 * 2);


    g.setColour(juce::Colours::lightgrey);
    g.fillRect(centeredRect);

    g.setColour(juce::Colours::black);
    g.drawRect(centeredRect, 2);

    g.drawText("Algorithm: " + std::to_string(algo_ind+1), x, y - 20, bounds.getHeight() / 3 * 2, 20, juce::Justification::centred, true);
}

void LFOComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::Rectangle<int> bounds = getLocalBounds();

    next_b->setBounds(bounds.getWidth() * 2 / 3, bounds.getHeight() / 5 - 20, 20, 20);
    prev_b->setBounds(bounds.getWidth() / 3 - 20, bounds.getHeight() / 5 - 20, 20, 20);
}
