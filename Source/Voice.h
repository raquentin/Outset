/*
  ==============================================================================

    Voice.h
    Created: 9 Mar 2025 12:40:33pm
    Author:  Quincy Winkler

  ==============================================================================
*/

#pragma once

struct Voice {
    void reset() {
        note = -1;
        velocity = 0;
    }
    
    int note;
    int velocity;
    
};
