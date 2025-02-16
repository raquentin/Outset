/*
  ==============================================================================

    FilterComp.cpp
    Created: 2 Feb 2025 12:46:44pm
    Author:  josep

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComp.h"

FilterComp::FilterComp()
{
    // Configure cutoff frequency knob (20 Hz to 20 kHz, logarithmic behavior)
    cutoffSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    cutoffSlider.setRange(20.0, 20000.0, 1.0);
    cutoffSlider.setSkewFactorFromMidPoint(1000.0);
    cutoffSlider.setValue(1000.0);
    cutoffSlider.addListener(this);
    addAndMakeVisible(cutoffSlider);

    // Configure resonance (Q) knob (range from 0.1 to 10, default 0.707 for Butterworth)
    resonanceSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    resonanceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    resonanceSlider.setRange(0.1, 10.0, 0.1);
    resonanceSlider.setValue(0.707);
    resonanceSlider.addListener(this);
    addAndMakeVisible(resonanceSlider);
}

FilterComp::~FilterComp()
{
}

void FilterComp::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::darkgrey);

    // Define drawing area for the frequency response (with margin)
    auto drawArea = getLocalBounds().reduced(10);

    // Draw horizontal grid lines (for reference)
    g.setColour(juce::Colours::grey);
    bool debug = false;
    if(debug)
    {
        for (int i = 0; i < 5; ++i)
        {
            float y = juce::jmap((float)i, 0.0f, 4.0f,
                (float)drawArea.getY(),
                (float)drawArea.getBottom());
            g.drawHorizontalLine(y, (float)drawArea.getX(), (float)drawArea.getRight());
        }
    }

    // Retrieve current cutoff and resonance from sliders
    float cutoff = (float)cutoffSlider.getValue();
    float Q = (float)resonanceSlider.getValue();

    // Compute TPT filter parameters
    // According to the TPT formulation:
    //   g = tan(pi * cutoff / sampleRate)
    //   R2 = 1 / Q
    //   D = 1 + R2 * g + g * g
    //   a0 = g^2 / D, a1 = 2*a0, a2 = a0
    //   b1 = -2*(1 - g^2)/D, b2 = (1 - R2*g + g*g)/D
    float gVal = std::tan(juce::MathConstants<float>::pi * cutoff / sampleRate);
    float R2 = 1.0f / Q;
    float D = 1.0f + R2 * gVal + gVal * gVal;
    float a0 = (gVal * gVal) / D;
    float a1 = 2.0f * a0;
    float a2 = a0;
    float b1 = -2.0f * (1.0f - gVal * gVal) / D;
    float b2 = (1.0f - R2 * gVal + gVal * gVal) / D;

    // Frequency range for drawing: from 20 Hz to Nyquist
    float minFreq = 20.0f;
    float maxFreq = sampleRate * 0.5f;

    juce::Path responseCurve;
    const int numPoints = drawArea.getWidth();

    // Define dB scale (0 dB at top, -60 dB at bottom)
    float maxDecibels = 20.0f;
    float minDecibels = -40.0f;

    bool firstPoint = true;
    bool inRange = false;
    float lastX = 0.0f, lastY = 0.0f;

    // Loop across the width and compute magnitude response at each frequency
    for (int i = 0; i < numPoints; ++i)
    {
        // Map x coordinate to frequency (logarithmically)
        float normX = (float)i / (float)(numPoints - 1);
        float freq = minFreq * std::pow(maxFreq / minFreq, normX);
        float omega = 2.0f * juce::MathConstants<float>::pi * freq / sampleRate;

        // Compute the complex frequency response H(e^(jω)) for the low-pass output:
        // H(e^(jω)) = (a0 + a1*e^(-jω) + a2*e^(-j2ω)) / (1 + b1*e^(-jω) + b2*e^(-j2ω))
        std::complex<float> expNegjOmega = std::exp(std::complex<float>(0, -omega));
        std::complex<float> expNegj2Omega = std::exp(std::complex<float>(0, -2 * omega));
        std::complex<float> numerator = a0 + a1 * expNegjOmega + a2 * expNegj2Omega;
        std::complex<float> denominator = std::complex<float>(1, 0) + b1 * expNegjOmega + b2 * expNegj2Omega;
        float magnitude = std::abs(numerator / denominator);

        // Convert magnitude to decibels
        float dB = juce::Decibels::gainToDecibels(magnitude);
        if (dB < minDecibels)
        {
            // If we were "inRange" on the previous sample, we can optionally
            // draw a line to the boundary:
            if (inRange)
            {
                // Compute intersection at dB = minDecibels:
                // Optionally do a little linear interpolation in the frequency domain
                // Or just lineTo the last X, Y clamped to minDbs. Example:
                float clippedY = juce::jmap(minDecibels,
                    maxDecibels, minDecibels,
                    (float)drawArea.getY(), (float)drawArea.getBottom());

                responseCurve.lineTo(lastX, clippedY);
            }
            inRange = false;
            // Do NOT do a lineTo, so we effectively skip drawing below minDbs.
        }
        else
        {
            // We are above minDecibels
            float clampedDb = juce::jlimit(minDecibels, maxDecibels, dB);
            float y = juce::jmap(clampedDb,
                maxDecibels, minDecibels,
                (float)drawArea.getY(), (float)drawArea.getBottom());
            float x = drawArea.getX() + (float)i;

            if (!inRange)
            {
                // Just transitioned from out-of-range to in-range,
                // so start a new subpath here
                responseCurve.startNewSubPath(x, y);
                inRange = true;
            }
            else
            {
                // Continue drawing
                responseCurve.lineTo(x, y);
            }

            // Keep track of last in-range point
            lastX = x;
            lastY = y;
        }
    }

    // Draw the frequency response curve in yellow
    g.setColour(juce::Colours::yellow);
    g.strokePath(responseCurve, juce::PathStrokeType(2.0f));
}

void FilterComp::resized()
{
    auto bounds = getLocalBounds().reduced(10);

    // Reserve the bottom 100 pixels for the knobs
    auto sliderArea = bounds.removeFromBottom(100);
    int sliderWidth = sliderArea.getWidth() / 2;

    cutoffSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(10));
    resonanceSlider.setBounds(sliderArea.reduced(10));
}

void FilterComp::sliderValueChanged(juce::Slider* slider)
{
    // When either knob changes, update the display
    repaint();
}
