#include <Arduino.h>
#include <Audio.h>

#include "Headers/Buffer.h"
#include "Headers/GrainProcess.h"
#include "Headers/Knob.h"
#include "Headers/Trigger.h"

using namespace std;

int samplerate = 44100;
int buffer_length = 10;

unsigned long last_time = micros();
unsigned long new_time;
float interval = 1000000.0f / samplerate;
float sample[2] = {0.0, 0.0};

Buffer in_buffer(samplerate * buffer_length);
Buffer out_buffer_left(samplerate * buffer_length);
Buffer out_buffer_right(samplerate * buffer_length);
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

// Initialize effect classes
GrainProcess gp(kDensity.getValue(), kSize.getValue(), kEnvelope.getValue(),kPitch.getValue(), samplerate, &in_buffer, &out_buffer_left, &out_buffer_right);

AudioSynthWaveformDc out_a;
AudioSynthWaveformDc out_b;
AudioOutputI2S i2s;

AudioConnection patchCord1(out_a, 0, i2s, 0);
AudioConnection patchCord2(out_b, 0, i2s, 1);

void setup() {
  AudioMemory(4);
}

void loop() {
  // Set a base timestamp
  new_time = micros();

  // Wrapper to handle micros() overflow
  if(new_time < last_time) {
    last_time = 0;
  }

  // Check timestamp against audio rate interval
  if(new_time - last_time >= interval) {
    gp.process();

    out_a.amplitude(out_buffer_left.getCurrentSample() * -1.0);
    out_b.amplitude(out_buffer_right.getCurrentSample() * -1.0);

    gp.tick();
    out_buffer_left.tick();
    out_buffer_right.tick();

    last_time = new_time;
  }
}