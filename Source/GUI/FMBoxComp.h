/*
  ==============================================================================

    FMBoxComp.h
    Created: 13 Feb 2025 2:39:50pm
    Author:  josep

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================
/*
*/
class FMBoxComp : public juce::Component
{
public:
    FMBoxComp();
    ~FMBoxComp() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void algorithm_1(juce::Graphics& g, juce::Rectangle<int> bounds);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FMBoxComp)
};
