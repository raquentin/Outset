/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OutsetAudioProcessorEditor::OutsetAudioProcessorEditor (OutsetAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    addAndMakeVisible(presets_comp);
    addAndMakeVisible(env_comp);
    addAndMakeVisible(filter_comp);
    addAndMakeVisible(keyboard_comp);
    addAndMakeVisible(lfo_comp);
    addAndMakeVisible(osc_comp);
    
}

OutsetAudioProcessorEditor::~OutsetAudioProcessorEditor()
{
}

//==============================================================================
void OutsetAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Probably will get rid of this because it'll get covered by the components
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Outset Island", getLocalBounds(), juce::Justification::centred, 1);
}

void OutsetAudioProcessorEditor::resized()
{
    // width and height variables
    int width_half = getWidth() / 2;
    int height_half = getHeight() / 2;
    int height_3rd = getHeight() / 3;
    int height_6th = getHeight() / 6;

    // setting the bounds here
    presets_comp.setBounds(0, 0, getWidth(), height_6th);
    osc_comp.setBounds(0, height_6th, width_half, height_3rd);
    filter_comp.setBounds(width_half, height_6th, width_half, height_3rd);
    env_comp.setBounds(0, height_half, width_half, height_3rd);
    lfo_comp.setBounds(width_half, height_half, width_half, height_3rd);
    keyboard_comp.setBounds(0, height_6th * 5, getWidth(), height_6th);
}
