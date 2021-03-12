//
// Created by Daniël Kamp on 04/03/2021.
//

#include "DryWetMixer.h"

DryWetMixer::DryWetMixer(float ratio, Buffer *input1, Buffer *input2, Buffer *output) {
  this->input1 = input1;
  this->input2 = input2;
  this->output = output;

  this->ratio = ratio;
}

DryWetMixer::~DryWetMixer() {}

void DryWetMixer::process() {
  output->write(ratio * input1->getCurrentSample() + (1.0 - ratio) * input2->getCurrentSample());
}

float DryWetMixer::processToValue() {
  return ratio * input1->getCurrentSample() + (1.0 - ratio) * input2->getCurrentSample();
}

void DryWetMixer::setRatio(float r) {
  if(r > 1) {
    ratio = 1.0;
  } else if(r < 0) {
    ratio = 0.0;
  } else {
    ratio = r;
  }
}