//
// Created by Daniël Kamp on 04/03/2021.
//

#ifndef _LOCALENV_DRYWETMIXER_H
#define _LOCALENV_DRYWETMIXER_H

#include "Buffer.h"

class DryWetMixer {
  public:
    DryWetMixer(float ratio, Buffer *input1, Buffer *input2, Buffer *output);
    ~DryWetMixer();

    void process();
    float processToValue();
    void setRatio(float ratio);
  private:
    Buffer *input1; // MONO input
    Buffer *input2; // "
    Buffer *output; // MONO output

    float ratio;
};


#endif //_LOCALENV_DRYWETMIXER_H
