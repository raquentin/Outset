/*
  ==============================================================================

    Synth.cpp
    Created: 9 Mar 2025 12:40:24pm
    Author:  Quincy Winkler

  ==============================================================================
*/

#include "Synth.h"


Synth::Synth()
{
//    sampleRate = 48000.0f;
}
void Synth::allocateResources(double sampleRate_, int /*samplesPerBlock*/)
{
    sampleRate = static_cast<float>(sampleRate_); 
}

void Synth::deallocateResources() 
{
// do nothing
}

void Synth::reset()
{
    voice.reset();
    noiseGen.reset();
}

void Synth::render(float** outputBuffers, int sampleCount)
{ //noise rendering from book. will replace with osc code later
    float* outputBufferLeft = outputBuffers[0];
    float* outputBufferRight = outputBuffers[1];
    
    for (int sample = 0; sample < sampleCount; ++sample) {
        float noise = noiseGen.nextValue();
        
        float output = 0.0f; 
        if (voice.note > -1) {
            output = noise * (voice.velocity / 127.0f) * 0.5f;
        }
        
        outputBufferLeft[sample] = output; 
        if (outputBufferRight != nullptr) {//conditional check for stereo
            outputBufferRight[sample] = output;
        }
    }
}

void Synth::noteOn(int note, int velocity) 
{
    voice.note = note;
    voice.velocity = velocity;
}
void Synth::noteOff(int note) 
{
    if (voice.note == note) { 
        voice.note = 0;
        voice.velocity = 0;
    }
}

void Synth::midiMessage(uint8_t data0, uint8_t data1, uint8_t data2)
{
    switch (data0 & 0xF0) { 
        // Note off
        case 0x80:
            noteOff(data1 & 0x7F);
            break;
            
        // Note on
        case 0x90:
            uint8_t note = data1 & 0x7F; //this mask in an abundance of caution
            uint8_t velo = data2 & 0x7F;
            if (velo > 0) {
                noteOn(note, velo);
            } else {
                noteOff(note);
            }
            break;
    }
}

