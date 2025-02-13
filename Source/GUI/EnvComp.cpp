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
    initializeSlider(attackSlider, "Attack", 0.0, 5.0, 0.01, 0.1);
    initializeSlider(decaySlider, "Decay", 0.0, 5.0, 0.01, 0.1);
    initializeSlider(sustainSlider, "Sustain", 0.0, 1.0, 0.01, 0.8);
    initializeSlider(releaseSlider, "Release", 0.0, 5.0, 0.01, 0.1);
}

EnvComp::~EnvComp()
{
}

void EnvComp::initializeSlider(juce::Slider& slider, const juce::String& name, double min, double max, double interval, double initialValue)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    slider.setRange(min, max, interval);
    slider.setValue(initialValue);
    slider.addListener(this);

    juce::Label* label = nullptr;
    if (name == "Attack") label = &attackLabel;
    else if (name == "Decay") label = &decayLabel;
    else if (name == "Sustain") label = &sustainLabel;
    else if (name == "Release") label = &releaseLabel;

    if (label != nullptr)
    {
        addAndMakeVisible(*label);
        label->setText(name, juce::dontSendNotification);
        label->setJustificationType(juce::Justification::centred);
    }
}

void EnvComp::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgreen);

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);

    g.setColour(juce::Colours::black);
    g.setFont(juce::Font(14.0f));
    //g.drawText("Envelopes", getLocalBounds(), juce::Justification::centred, true);

    // Draw ADSR graph
    auto bounds = getLocalBounds().reduced(10);
    auto width = bounds.getWidth();
    auto height = bounds.getHeight();

    float attack = attackSlider.getValue();
    float decay = decaySlider.getValue();
    float sustain = sustainSlider.getValue();
    float release = releaseSlider.getValue();

    juce::Path adsrPath;
    adsrPath.startNewSubPath(bounds.getX(), bounds.getBottom());
    adsrPath.lineTo(bounds.getX() + width * (attack / (attack + decay + release)), bounds.getY());
    adsrPath.lineTo(bounds.getX() + width * ((attack + decay) / (attack + decay + release)), bounds.getY() + height * (1.0f - sustain));
    adsrPath.lineTo(bounds.getX() + width * ((attack + decay + release) / (attack + decay + release)), bounds.getBottom());

    g.setColour(juce::Colours::blue);
    g.strokePath(adsrPath, juce::PathStrokeType(2.0f));
    // Debug Grid Lines
    bool debug = true;
    if (!debug) return;
    bounds = getLocalBounds();
    width = bounds.getWidth();
    height = bounds.getHeight();
    g.setColour(juce::Colours::grey);

    // Draw vertical grid lines: every 1/6 of the total width
    for (int i = 1; i < 6; ++i)
    {
        float x = (width * i) / 6.0f;
        g.drawLine(x, 0.0f, x, (float)height);
    }

    // Draw horizontal grid lines: every 1/4 of the total height
    for (int j = 1; j < 4; ++j)
    {
        float y = (height * j) / 4.0f;
        g.drawLine(0.0f, y, (float)width, y);
    }

    //g.setColour(juce::Colours::red);
    //drawSliderOutline(g, oscLevelSlider);
    //drawSliderOutline(g, oscFineTuneSlider);
    //drawSliderOutline(g, oscCoarseTuneSlider);
    //drawSliderOutline(g, oscRatioSlider);
    //drawSliderOutline(g, oscFeedbackSlider);
}

void EnvComp::resized()
{
    auto bounds = getLocalBounds();
	auto width = bounds.getWidth();
	auto height = bounds.getHeight();

    auto height_half = height / 2;
	auto width_half = width / 2;
	auto width_3rd = width / 3;

    auto attackSliderArea = bounds;
    auto decaySliderArea = bounds;
    auto sustainSliderArea = bounds;
    auto releaseSliderArea = bounds;

    auto knob_size = bounds.getHeight() / 4;

    attackSliderArea = attackSliderArea.removeFromBottom(height_half / 2).reduced(width_half / 3, 0).withSizeKeepingCentre(knob_size, knob_size);
    decaySliderArea = decaySliderArea.removeFromBottom(height_half / 2).removeFromLeft(width_3rd - knob_size / 2).withSizeKeepingCentre(knob_size, knob_size);
    sustainSliderArea = sustainSliderArea.removeFromBottom(height_half / 2).removeFromRight(width_3rd + knob_size * 2).withSizeKeepingCentre(knob_size, knob_size);
    releaseSliderArea = releaseSliderArea.removeFromBottom(height_half / 2).removeFromRight(width_3rd).withSizeKeepingCentre(knob_size, knob_size);

    // Set bounds for each slider and label
    setSliderBounds(attackSlider, attackLabel, attackSliderArea);
    setSliderBounds(decaySlider, decayLabel, decaySliderArea);
    setSliderBounds(sustainSlider, sustainLabel, sustainSliderArea);
    setSliderBounds(releaseSlider, releaseLabel, releaseSliderArea);
}

void EnvComp::sliderValueChanged(juce::Slider* slider)
{
    repaint();
}

void EnvComp::setSliderBounds(juce::Slider& slider, juce::Label& label, juce::Rectangle<int> bounds)
{
    slider.setBounds(bounds);
    if (slider.getSliderStyle() != juce::Slider::SliderStyle::LinearHorizontal)
        label.setBounds(bounds.withHeight(20).translated(0, -20).expanded(10, 0)); // Place the label above the slider
    else
        label.setBounds(bounds.withHeight(20).translated(0, 20).expanded(10, 0));
}
