/*
  ==============================================================================

    LFOComp.h
    Created: 2 Feb 2025 12:49:27pm
    Author:  josep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LFOComp  : public juce::Component
{
public:
    LFOComp();
    ~LFOComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    int algo_ind;
    std::unique_ptr<juce::DrawableButton> next_b;
    std::unique_ptr<juce::DrawableButton> prev_b;
    juce::Image image;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComp)
};
