/*
  ==============================================================================

    EnvComp.h
    Created: 2 Feb 2025 12:46:52pm
    Author:  josep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EnvComp : public juce::Component, private juce::Slider::Listener
{
public:
    EnvComp();
    ~EnvComp() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void initializeSlider(juce::Slider& slider, const juce::String& name, double min, double max, double interval, double initialValue, bool skewed);
    void sliderValueChanged(juce::Slider* slider) override;
    void setSliderBounds(juce::Slider& slider, juce::Label& label, juce::Rectangle<int> bounds);
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvComp)
};


