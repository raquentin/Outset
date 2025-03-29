/*
  ==============================================================================

    FilterComp.h
    Created: 2 Feb 2025 12:46:44pm
    Author:  josep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterComp : public juce::Component,
    public juce::Slider::Listener
{
public:
    FilterComp();
    ~FilterComp() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Slider callback
    void sliderValueChanged(juce::Slider* slider) override;

    // Optionally, update the sample rate used for response calculation
    void setSampleRate(float newSampleRate) { sampleRate = newSampleRate; repaint(); }

private:
    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;

    juce::Label freqLabel;
    juce::Label qLabel;

    juce::TextEditor cutoffTextBox;
    juce::TextEditor resonanceTextBox;

    // Sample rate used for computing the response curve (default: 44100 Hz)
    float sampleRate = 44100.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterComp)
};

