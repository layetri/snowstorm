//
// Created by Daniël Kamp on 12/02/2021.
//

#ifndef SNOWSTORM_GRAIN_H
#define SNOWSTORM_GRAIN_H

#include "Buffer.h"
#include "Envelope.h"
#include "Filter.h"

class Grain {
public:
    Grain(Buffer *buffer);
    virtual ~Grain();

private:
    bool active; // Grain is playing
    bool random; // Grain is triggered randomly

    int position; // Position in the input's buffer
    int length; // Length of the buffer

    float sample; // The current sample
    float speed; // The playback speed

};


#endif //SNOWSTORM_GRAIN_H
