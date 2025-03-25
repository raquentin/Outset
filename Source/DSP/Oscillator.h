/*
  ==============================================================================

    Oscillator.h
    Created: 9 Mar 2025 3:21:55pm
    Author:  Quincy Winkler

  ==============================================================================
*/

#pragma once


const float TWO_PI = 6.2831853071795864f;
class Oscillator {
public:
    float amplitude; 
    float inc;
    float phase;
//    float freq;
//    float sampleRate; 
//    float phaseOffset;
//    int sampleIndex;
    
    void reset()
    {
//        sampleIndex = 0;
        phase = 0.0f;
    }
    float nextSample()
    {
        phase += inc;
        if (phase >= 1.0f) {
            phase -= 1.0f;
        }
        
        return amplitude * std::sin(TWO_PI * phase);
//        float output = amplitude * std::sin(TWO_PI * sampleIndex * freq / sampleRate + phaseOffset);
//        sampleIndex += 1;
//        return output;
    }
};
