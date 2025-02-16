/*
  ==============================================================================

    KeyboardComp.h
    Created: 2 Feb 2025 12:49:37pm
    Author:  josep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//==============================================================================
/*
*/
class KeyboardComp  : public juce::Component
{
public:
    KeyboardComp();
    ~KeyboardComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComp)
};
