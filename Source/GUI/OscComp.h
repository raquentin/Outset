/*
  ==============================================================================

    EnvComp.h
    Created: 2 Feb 2025 12:46:52pm
    Author:  josep, ryanb

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscComp : public juce::Component, private juce::Slider::Listener
{
public:
    OscComp(const juce::String& title = "title");
    ~OscComp() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void initializeSlider(juce::Slider& slider, juce::Label& label, const juce::String& name, juce::Slider::SliderStyle style, double min, double max, double interval, double initialValue);
    void setSliderBounds(juce::Slider& slider, juce::Label& label, juce::Rectangle<int> bounds);
    void drawSliderOutline(juce::Graphics& g, juce::Slider& slider);
    void addLabel(juce::Slider& slider, juce::Label& label, const juce::String& name);
    void sliderValueChanged(juce::Slider* slider) override;
    void updateLabel(juce::Label& label, const juce::String& name, double value);

    juce::String tabTitle;

    juce::Slider oscLevelSlider;
    juce::Slider oscFineTuneSlider;
    juce::Slider oscRatioSlider;

    juce::Label oscLevelLabel;
    juce::Label oscFineTuneLabel;
    juce::Label oscRatioLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComp)
};
