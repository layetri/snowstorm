//
// Created by Daniël Kamp on 03/03/2021.
//

#include "Grain.h"

#include <iostream>

Grain::Grain(int order, int length, int start, Buffer *buffer) {
  this->buffer = buffer;
  this->order = order;

  this->length = length;
  this->start = start;
  position = 0;

  _cleanup_countdown = length;

  wrapLength();

  _active = false;
  _schedule_cleanup = false;
}
Grain::~Grain() {}

float *Grain::process(float env_length, int env_shape, float spatialize) {
  if(checkPosition()) {
    float tmp = buffer->getCurrentSample();

    int env_size = env_length * length;
    lEnvSize = env_size;
    if(env_shape == 0) {
      // Handle linear
      // TODO: fix this thing.
      //    -> it pops?
      if(position <= env_size) {
        // Rise
        tmp = tmp * position * (1.0 / env_size);
      } else if(position >= length - env_size) {
        // Fall
        tmp = tmp * (1.0 - (position - (length - env_size)) * (1.0 / env_size));
      }
    } else {
       // Handle exponential
//       if(position < env_size) {
//         tmp = tmp * env_step * pow(position, 2);
//       } else {
//         tmp = tmp * env_step * pow(position * -1, 2) + 1;
//       }
    }

    if(spatialize > 0.0 && spatializer < spatialize) {
      // First, randomly select a channel

      if(channelizer > 0.5) {
        // Pan to the right
        sample[0] = tmp * ((1.0 - spatializer) / 2);
        sample[1] = tmp * ((1.0 + spatializer) / 2);
      } else {
        // Pan to the left
        sample[0] = tmp * ((1.0 + spatializer) / 2);
        sample[1] = tmp * ((1.0 - spatializer) / 2);
      }
    } else {
      sample[0] = tmp * 0.5;
      sample[1] = tmp * 0.5;
    }

    position++;
  } else {
    sample[0] = 0.0;
    sample[1] = 0.0;
  }

  return sample;
}

int Grain::check() {
  if(!_active && !_schedule_cleanup) {
    // Grain isn't active or scheduled for deletion, check position
    if (checkPosition()) {
      _active = true;
      position = 0;

      // Set spatialization values
      spatializer = (float) random();
      channelizer = (float) random();

      return 1;
    }
  } else if(!_active && _schedule_cleanup) {
    // Make sure that the grain can't be deleted while still part of the cycle
    if(_cleanup_countdown > 0) {
      _cleanup_countdown -= 1;
      return 0;
    } else {
      // Grain is scheduled for deletion
      return 2;
    }
  } else if(_active && !checkPosition()) {
    // Grain is no longer active
    deactivate();
  } else if(_active) {
    // Grain is active
    return 3;
  }
  return 0;
}

void Grain::deactivate() {
  _active = false;
}

void Grain::scheduleCleanup() {
  _schedule_cleanup = true;
}

void Grain::loop() {
  _loop = !_loop;
}

void Grain::setLength(int nLength) {
  length = nLength;
  _cleanup_countdown = length;

  wrapLength();
}

void Grain::calculateStart(int division) {
  start = order * division;
  wrapLength();
}

void Grain::wrapLength() {
  end = start + length;

  if(end > buffer->getSize()) {
    end -= buffer->getSize();
  }
}

bool Grain::checkPosition() {
  // Check if the buffer crosses 0
  if(start > end) {
    return buffer->getPosition() > start || buffer->getPosition() < end;
  } else {
    return buffer->getPosition() > start && buffer->getPosition() < end;
  }
}

int Grain::getOrder() {
  return order;
}

int Grain::getStart() {
  return start;
}

void Grain::print() {
  std::cout << latest_output << std::endl;
  std::cout << "Grain: " << order << " start: " << start << " length: " << length << " end: " << end << " envelope_size: " << lEnvSize << std::endl;
}
