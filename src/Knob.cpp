#include "Headers/Knob.h"

Knob::Knob(int pin) {
  pinMode(pin, INPUT);
  this->pin = pin;
}

Knob::~Knob() {}

float Knob::getValue() {
  value = analogRead(pin) / 1023.0;
  return value;
}