//
// Created by Daniël Kamp on 17/02/2021.
//

#include "Headers/Buffer.h"

Buffer::Buffer(int length) {
  data = new float[length];
}

Buffer::~Buffer() {
  delete[] data;
}

int Buffer::getSize() {
  return size;
}

float Buffer::getSample(int sample_position = position) {
  return this->operator[](sample_position);
}

void Buffer::tick() {
  if(position < size) {
    position++;
  } else {
    position -= size;
  }
}