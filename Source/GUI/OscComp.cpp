/*
  ==============================================================================

    EnvComp.h
    Created: 2 Feb 2025 12:46:52pm
    Author:  josep, ryanb

  ==============================================================================
*/
#include "OscComp.h"

OscComp::OscComp(const juce::String& title)
    : tabTitle(title)
{
    initializeSlider(oscLevelSlider, oscLevelLabel, "Level", juce::Slider::SliderStyle::LinearVertical, 0.0, 1.0, 0.01, 0.5);
    initializeSlider(oscFineTuneSlider, oscFineTuneLabel, "Fine Tune", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, -50.0, 50.0, 0.01, 0.0);
    initializeSlider(oscRatioSlider, oscRatioLabel, "Ratio", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, -12.0, 12.0, 1.0, 0.0);
}

void OscComp::paint(juce::Graphics& g)
{
    // Debug Grid Lines
    bool debug = false;
    if (!debug) return;
    g.setColour(juce::Colours::grey);

    auto width = getWidth();
    auto height = getHeight();

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

    g.setColour(juce::Colours::red);
    drawSliderOutline(g, oscLevelSlider);
    drawSliderOutline(g, oscFineTuneSlider);
    drawSliderOutline(g, oscRatioSlider);
}

void OscComp::resized()
{
    auto bounds = getLocalBounds();
    auto height = bounds.getHeight();
    auto width = bounds.getWidth();
    auto width_half = width / 2;
    auto width_3rd = width / 3;
    auto height_half = height / 2;
    auto height_3rd = height / 3;

    int small_knob_size = width_half / 3;
    int big_knob_size = width_half / 2;

    auto levelSliderArea = bounds;
    auto fineTuneSliderArea = bounds;
    auto coarseTuneSliderArea = fineTuneSliderArea;
    auto ratioSliderArea = fineTuneSliderArea;
    auto feedbackSliderArea = fineTuneSliderArea;

    fineTuneSliderArea = fineTuneSliderArea.removeFromBottom(height).removeFromLeft(width_3rd - small_knob_size / 2).withSizeKeepingCentre(small_knob_size, small_knob_size);
    levelSliderArea = levelSliderArea.removeFromBottom(height).removeFromRight(width_3rd + big_knob_size * 2).withSizeKeepingCentre(big_knob_size, big_knob_size);
    ratioSliderArea = ratioSliderArea.removeFromBottom(height).removeFromRight(width_3rd).withSizeKeepingCentre(big_knob_size, big_knob_size);

    // Set bounds for each slider and label
    setSliderBounds(oscLevelSlider, oscLevelLabel, levelSliderArea);
    setSliderBounds(oscFineTuneSlider, oscFineTuneLabel, fineTuneSliderArea);
    setSliderBounds(oscRatioSlider, oscRatioLabel, coarseTuneSliderArea);
}

void OscComp::initializeSlider(juce::Slider& slider, juce::Label& label, const juce::String& name, juce::Slider::SliderStyle style, double min, double max, double interval, double initialValue)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(style);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    slider.setRange(min, max, interval);
    slider.setValue(initialValue);
    slider.addListener(this);
    slider.setDoubleClickReturnValue(true, initialValue);
    addLabel(slider, label, name);
}

void OscComp::setSliderBounds(juce::Slider& slider, juce::Label& label, juce::Rectangle<int> bounds)
{
    slider.setBounds(bounds);
    if (slider.getSliderStyle() != juce::Slider::SliderStyle::LinearHorizontal)
        label.setBounds(bounds.withHeight(20).translated(0, -20).expanded(10, 0)); // Place the label above the slider
    else
        label.setBounds(bounds.withHeight(20).translated(0, 20).expanded(10, 0));
}

void OscComp::drawSliderOutline(juce::Graphics& g, juce::Slider& slider)
{
    g.drawRect(slider.getBounds(), 2); // Draw a red outline with a thickness of 2
}

void OscComp::addLabel(juce::Slider& slider, juce::Label& label, const juce::String& name)
{
    label.setText(name + ": " + juce::String(slider.getValue()), juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void OscComp::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &oscLevelSlider)
        updateLabel(oscLevelLabel, "Level", slider->getValue());
    else if (slider == &oscFineTuneSlider)
        updateLabel(oscFineTuneLabel, "Fine Tune", slider->getValue());
    else if (slider == &oscRatioSlider)
        updateLabel(oscRatioLabel, "Ratio", slider->getValue());
}

void OscComp::updateLabel(juce::Label& label, const juce::String& name, double value)
{
    label.setText(name + ": " + juce::String(value), juce::dontSendNotification);
    int textWidth = label.getFont().getStringWidth(label.getText());
    label.setSize(textWidth + 10, label.getHeight()); // Add some padding to the width
}