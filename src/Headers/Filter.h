//
// Created by Daniël Kamp on 12/02/2021.
//

#ifndef SNOWSTORM_FILTER_H
#define SNOWSTORM_FILTER_H

#include <iostream>
#include "Buffer.h"


class Filter {
public:
    Filter(float frequency, int samplerate, Buffer *input, Buffer *output);
    virtual ~Filter();

    float process();
    void tick();

    void setFrequency(float frequency);
    float getFrequency();
    int getDelay();

    virtual float calculateSample();
    virtual void frequencyHandler();

protected:
    Buffer *input;
    Buffer *output;
    float frequency;
    float sample;
    double ff;

    int samplerate;
    int index;
    int delayTime;
    int buffer_size;
};


#endif //SNOWSTORM_FILTER_H
