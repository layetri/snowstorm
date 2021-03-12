//
// Created by Daniël Kamp on 25/02/2021.
//

#ifndef _SNOWSTORM_LOWPASSFILTER_H
#define _SNOWSTORM_LOWPASSFILTER_H

#include "Filter.h"
#include <cmath>

class LowPassFilter : public Filter {
  public:
    LowPassFilter(float, int, Buffer*, Buffer*);
    ~LowPassFilter();

    float calculateSample() override;
    void frequencyHandler() override;

  private:
    // Filter coefficients, butterworth-style
    double b0, b1, b2, a1, a2;
};


#endif //_SNOWSTORM_LOWPASSFILTER_H
