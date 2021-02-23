#include <Arduino.h>
#include "Headers/Buffer.h"
#include "Headers/GrainDelay.h"
#include "Headers/Knob.h"
#include "Headers/Trigger.h"

using namespace std;

int samplerate = 44100;
int buffer_length = 10;

Buffer in_buffer(samplerate * buffer_length);
Buffer out_buffer(samplerate * buffer_length);
int read_in;
int read_out;

// Initialize hardware
Knob kPosition(1);
Knob kSize(2);
Knob kPitch(3);
Knob kDensity(4);
Knob kEnvelope(5);
Knob kBlend(6);

Trigger bBlend(12, true);

GrainDelay gd;

void setup() {
// write your initialization code here
}

void loop() {
// write your code here
  gd.tick();
}