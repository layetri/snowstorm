#pragma once
#include "Arduino.h"

class Knob {
  public:
    explicit Knob(int pin);
    ~Knob();

    float getValue();

  private:
    int pin;
    float value;
};