//
// Created by Daniël Kamp on 03/03/2021.
//

#ifndef _LOCALENV_GRAIN_H
#define _LOCALENV_GRAIN_H

#include "Buffer.h"
#include <Arduino.h>

class Grain {
  public:
    Grain(int order, int length, int start, Buffer*);
    ~Grain();

    // Process for a single tick
    float *process(float envelope_length, int envelope_shape, float spatialize);
    // Run a check on the buffer
    int check();
    // Enable looped mode
    void loop();

    void deactivate();

    void setLength(int nLength);
    void calculateStart(int division);

    void wrapLength();
    void scheduleCleanup();

    float applyWindowing(float, float, int) const;

    bool checkPosition();
    int getOrder();
    int getStart();
  private:
    Buffer *buffer;

    float sample[2];

    // Has order, length, position, speed
    int order;
    int length;
    int position;
    int start;
    int end;
    float speed;

    float spatializer;
    float channelizer;

    bool _loop;
    bool _active;

    // Only allow deletion after a new buffer has started playing
    bool _schedule_cleanup;
    int _cleanup_countdown;
};


#endif //_LOCALENV_GRAIN_H
