//
// Created by Daniël Kamp on 12/02/2021.
//

#ifndef SNOWSTORM_FILTER_H
#define SNOWSTORM_FILTER_H

#include <iostream>
#include "Buffer.h"


class Filter {
public:
    Filter(float frequency, float samplerate, Buffer *buffer);
    virtual ~Filter();

    float getSample() const;
    void tick();

    void setFrequency(float frequency);

private:
    Buffer *buffer;
    float frequency;
    float sample;

    int index;
    int delayTime;
    int buffer_size;
};


#endif //SNOWSTORM_FILTER_H
