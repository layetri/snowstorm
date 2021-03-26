//
// Created by Daniël Kamp on 03/03/2021.
//

#ifndef _LOCALENV_GRAINPROCESS_H
#define _LOCALENV_GRAINPROCESS_H

#include "Buffer.h"
#include "Grain.h"
#include <cmath>
#include <vector>

class GrainProcess {
  public:
    GrainProcess(
        float spread, float size, float shape, float speed,
        int samplerate, Buffer* input, Buffer* outputL, Buffer* outputR
      );
    ~GrainProcess();

    void process();
    void tick();

    void processParameterChanges(float spread, float size, float shape, float speed);
    void freeze();

    void setSpread(int spread);
    void setSize(int size);
    void setShape(int shape);
    void setStereo(int stereo);
  private:
    // Buffers and pointers etc
    Buffer *input;
    Buffer *outputL;
    Buffer *outputR;
    Buffer *buffer;
    // Use a vector for grain administration
    std::vector<Grain*> tracklist;
    int tracklist_size;

    void performMapping();

    // Sysvars
    int samplerate;
    int position;
    int length;

    // Store external parameters
    float spread;
    float size;
    float shape;
    float speed;

    // Store mappings
    int nGrains;
    int divisionLen;
    int grainLen;
    bool rGrainLen;
    float stereo;

    float env_length;
    int env_shape;

    bool _freeze;
    bool _grain_set;
};


#endif //_LOCALENV_GRAINPROCESS_H
