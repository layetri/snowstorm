//
// Created by Daniël Kamp on 17/02/2021.
//

#include "Buffer.h"

#include <iostream>

Buffer::Buffer(int length, std::string name) {
  data = new float[length];
  size = length;
  position = 0;
  this->name = name;
}

Buffer::~Buffer() {
  delete[] data;
}

int Buffer::getSize() {
  return size;
}

int Buffer::getPosition() {
  return position;
}

float Buffer::getSample(int sample_position) {
  if(sample_position < 0) {
    return this->operator[](size + sample_position);
  } else {
    return this->operator[](sample_position);
  }
}

float Buffer::getCurrentSample() {
  return this->operator[](position);
}

void Buffer::tick() {
  if(position < size) {
    position++;
  } else {
    position -= size;
    //std::cout << position << ", " << size << ": Buffer returning (" << name << ", " << getCurrentSample() << ")" << std::endl;
  }
}

void Buffer::write(float sample) {
  data[position] = sample;
}