/*
  ==============================================================================

    OscComp.cpp
    Created: 2 Feb 2025 12:46:52pm
    Author:  josep, ryanb

  ==============================================================================
*/
#include "OscComp.h"
#include <string>

OscComp::OscComp(int num, juce::AudioProcessorValueTreeState& apvtsRef)
    : oscNum(num),
      apvtsRef(apvtsRef),
      levelAttachment(apvtsRef, "LEVEL_" + std::to_string(oscNum), oscLevelSlider),
      fineAttachment(apvtsRef, "FINE_" + std::to_string(oscNum), oscFineSlider),
      coarseAttachment(apvtsRef, "COARSE_" + std::to_string(oscNum), oscCoarseSlider)
      
{
    // setup the sliders
    initializeSlider(oscLevelSlider, oscLevelLabel, "Level", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0, 1.0, 0.01, 0.5);
    initializeSlider(oscFineSlider, oscFineLabel, "Fine", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0, 100.0, 1.0, 0.0);
    initializeSlider(oscCoarseSlider, oscCoarseLabel, "Coarse", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, 1.0, 12.0, 1.0, 1.0);
    
    // again kinda spamming the same colors everywhere, we can do a pr to pull it out
    juce::Colour mainBlue(0x91, 0xC9, 0xB5);
    juce::Colour accentBlue(0x5B, 0x8F, 0x7E);
    
    for (auto* slider : {&oscLevelSlider, &oscFineSlider, &oscCoarseSlider})
    {
        slider->setColour(juce::Slider::rotarySliderFillColourId, mainBlue);
        slider->setColour(juce::Slider::rotarySliderOutlineColourId, accentBlue);
        slider->setColour(juce::Slider::thumbColourId, juce::Colours::white);
    }
    
    // TODO: juce funt deprecated
    for (auto* label : {&oscLevelLabel, &oscFineLabel, &oscCoarseLabel})
    {
        label->setFont(juce::Font(14.0f, juce::Font::bold));
        label->setColour(juce::Label::textColourId, mainBlue);
        label->setJustificationType(juce::Justification::centred);
    }
}

void OscComp::paint(juce::Graphics& g)
{
    // TODO: de-dupe colors
    juce::Colour mainBlue(0x91, 0xC9, 0xB5);
    juce::Colour accentBlue(0x5B, 0x8F, 0x7E);
    juce::Colour backgroundColour(0x1A, 0x1A, 0x1A);
    
    // bg and border
    g.fillAll(backgroundColour);
    g.setColour(accentBlue);
    g.drawRect(getLocalBounds(), 1);
    
    // DRAW OSC
    auto bounds = getLocalBounds().reduced(14); // padding
    auto height = bounds.getHeight() * 0.5; // half the height
    auto graphBounds = bounds.withHeight(height);
    
    
    juce::Path wavePath;
    float amplitude = height / 2.0f * oscLevelSlider.getValue();
    float centerY = graphBounds.getCentreY();
    float ratio = oscCoarseSlider.getValue();
    float fineTune = oscFineSlider.getValue() / 25.0f;
    
    // The thing about fractional ratios
    ratio = std::max(1.0f, std::abs(ratio));
    
    wavePath.startNewSubPath(graphBounds.getX(), centerY);
    
    for (int x = 0; x < graphBounds.getWidth(); ++x)
    {
        float t = (float)x / graphBounds.getWidth() * juce::MathConstants<float>::twoPi * ratio;
        t += fineTune;
        float y = centerY - std::sin(t) * amplitude;
        wavePath.lineTo(graphBounds.getX() + x, y);
    }
    
    g.setColour(mainBlue);
    g.strokePath(wavePath, juce::PathStrokeType(2.0f));
    
    // classic gradient
    juce::Path fillPath = wavePath;
    fillPath.lineTo(graphBounds.getRight(), centerY);
    fillPath.lineTo(graphBounds.getX(), centerY);
    fillPath.closeSubPath();
    g.setGradientFill(juce::ColourGradient(
        mainBlue.withAlpha(0.15f),
        graphBounds.getX(), graphBounds.getY(),
        mainBlue.withAlpha(0.05f),
        graphBounds.getX(), graphBounds.getBottom(),
        false));
    g.fillPath(fillPath);
    
    // grid lines
    g.setColour(juce::Colours::white.withAlpha(0.2f));
    for (int i = 1; i < 5; ++i)
    {
        float xPos = graphBounds.getX() + (graphBounds.getWidth() * i) / 5.0f;
        g.drawLine(xPos, graphBounds.getY(), xPos, graphBounds.getBottom(), 1.0f);
    }
    
    // middle line
    float centerLine = graphBounds.getCentreY();
    g.drawLine(graphBounds.getX(), centerLine, graphBounds.getRight(), centerLine, 1.0f);
    
    // vals on sliders same as ENV
    g.setColour(mainBlue);
    g.setFont(juce::Font(12.0f));
    // lambda for printing the vals
    auto valueStr = [](float value) { return juce::String(value, 2); };
    g.drawText(valueStr(oscLevelSlider.getValue()),
              oscLevelSlider.getBounds().translated(0, -15),
              juce::Justification::centred);
    g.drawText(valueStr(oscFineSlider.getValue()),
              oscFineSlider.getBounds().translated(0, -15),
              juce::Justification::centred);
    g.drawText(valueStr(oscCoarseSlider.getValue()),
              oscCoarseSlider.getBounds().translated(0, -15),
              juce::Justification::centred);
}

void OscComp::resized()
{
    auto bounds = getLocalBounds();
    
    // half height is wavepath
    auto visualHeight = bounds.getHeight() * 0.5;
    bounds.removeFromTop(visualHeight);
    
    // bottom half is sliders
    auto sliderArea = bounds;
    auto sliderWidth = sliderArea.getWidth() / 3;
    
    auto knobSize = juce::jmin(sliderWidth * 0.6f, 35.0f);
    
    // align
    auto levelArea = sliderArea.removeFromLeft(sliderWidth);
    auto fineArea = sliderArea.removeFromLeft(sliderWidth);
    auto ratioArea = sliderArea;
    
    oscLevelSlider.setBounds(levelArea.withSizeKeepingCentre(knobSize, knobSize));
    oscFineSlider.setBounds(fineArea.withSizeKeepingCentre(knobSize, knobSize));
    oscCoarseSlider.setBounds(ratioArea.withSizeKeepingCentre(knobSize, knobSize));
    
    // labels below sliders
    oscLevelLabel.setBounds(oscLevelSlider.getBounds().withHeight(20).translated(0, knobSize/2 + 5));
    oscFineLabel.setBounds(oscFineSlider.getBounds().withHeight(20).translated(0, knobSize/2 + 5));
    oscCoarseLabel.setBounds(oscCoarseSlider.getBounds().withHeight(20).translated(0, knobSize/2 + 5));
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
    
    addAndMakeVisible(label);
    label.setText(name, juce::dontSendNotification);
}

void OscComp::sliderValueChanged(juce::Slider* slider)
{
    repaint();
}

// I liberally removed some things here bc i didnt use them lmk if they are needed
