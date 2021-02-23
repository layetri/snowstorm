//
// Created by Daniël Kamp on 12/02/2021.
//

#include "Headers/Filter.h"


Filter::Filter(float frequency, float samplerate, Buffer *buffer) {
  this->buffer = buffer;
  buffer_size = buffer->getSize();
  sample = 0.0;

  setFrequency(frequency);
}

Filter::~Filter() {}

void Filter::tick() {
  // Wrap the filter function around the circular buffer
  if(index - delayTime > 0) {
    sample = (buffer->getSample(index) + buffer->getSample(index - delayTime)) * 0.5f;
  } else {
    sample = (buffer->getSample(index) + buffer->getSample(buffer_size - (delayTime - index))) * 0.5f;
  }

  // Wrap the index around the circular buffer
  if(index < buffer_size) {
    index++;
  } else {
    index -= buffer_size;
  }
}

float Filter::getSample() const {
  return sample;
}

void Filter::setFrequency(float set_frequency) {
  if(set_frequency != frequency) {
    delayTime = (int) (44100.0 / set_frequency);
    frequency = set_frequency;
  }
}
