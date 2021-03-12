//
// Created by Daniël Kamp on 25/02/2021.
//

#ifndef _SNOWSTORM_DELAYLINE_H
#define _SNOWSTORM_DELAYLINE_H

#include "Buffer.h"
#include "LowPassFilter.h"

class DelayLine {
  public:
    DelayLine(int delayTime, float feedback, Buffer *input);
    ~DelayLine();

    float process();
    void tick();

    void setDelayTime(int delayTime);
    int getDelayTime();

    void setdf(int delayTime, float feedback);

  protected:
    Buffer *x;
    Buffer *y;

    float feedback;

    int delayTime;
    int position;
};


#endif //_SNOWSTORM_DELAYLINE_H
