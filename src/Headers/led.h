#pragma once
#include "Arduino.h"

class LED {
  public:
    LED(int pin);
    ~LED();

    void setPattern(int pattern);
    void cycle();
    void on();
    void off();

  private:
    bool status;
    bool steady;

    int pin;
    int pattern;
    int patterns[4] = {0, 100, 200, 300};

    int timer;
    int timeout;
};
