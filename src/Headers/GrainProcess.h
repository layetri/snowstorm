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
        int spread, int size, int shape, int speed,
        int samplerate, Buffer* input, Buffer* outputL, Buffer* outputR
      );
    ~GrainProcess();

    void process();
    void tick();

    void processParameterChanges(int spread, int size, int shape, int speed);
    void freeze();

    void setSpread(int spread);
    void setSize(int size);
    void setShape(int shape);
    void setStereo(int stereo);

    void printGrains();

    bool delflag;
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
    int spread; // Density of the output
    int size; // Global grain size
    int shape; // Global envelope
    int speed; // Global playback speed

    // Store mappings
    int nGrains; // Number of grains (time-linear)
    int divisionLen; // Length of each slice (within which the grain is scheduled)
    int grainLen; // Default grain length
    bool rGrainLen; // Randomize buffer length
    float stereo; // Stereo spread deviation factor

    bool _freeze; // Freeze audio
    bool _grain_set; // Flag to indicate grain status;

    // TODO: implement Envelope
    //    -> for linear envelope:
    //    -> attack/decay are the same length
    float env_length;
    int env_shape;

};


#endif //_LOCALENV_GRAINPROCESS_H
