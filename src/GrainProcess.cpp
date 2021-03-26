//
// Created by Daniël Kamp on 03/03/2021.
//

#include "Headers/GrainProcess.h"

GrainProcess::GrainProcess(
  // Knob params
  float spread, float size, float shape, float speed,
  // System params
  int samplerate, Buffer *input, Buffer *outputL, Buffer *outputR) {
    // Assign buffers
    this->input = input;
    this->outputL = outputL;
    this->outputR = outputR;
    length = samplerate;
    buffer = new Buffer(length);

    // Store relevant sysvars
    this->samplerate = samplerate;
    _grain_set = false;
    _freeze = false;
    position = 0;

    // Store readouts
    this->spread = spread;
    this->size = size;
    this->shape = shape;
    this->speed = speed;

    // Map readouts
    performMapping();
    setStereo(1000);

    for(int i = 0; i < nGrains; i++) {
      // Vector keeps order, so grains will always be in order
      //    -> index is safe to do MATHS with
      tracklist.push_back(new Grain(i, grainLen, i * divisionLen, buffer));
    }

    _grain_set = true;
    tracklist_size = tracklist.size();
}

GrainProcess::~GrainProcess() {
  for(int i = 0; i < tracklist_size; i++) {
    tracklist.erase(tracklist.begin() + i);
  }
}

void GrainProcess::process() {
  std::vector<Grain*> activeGrains;

  // For each grain, run check
  for(int i = 0; i < tracklist_size; i++) {
    int grain_sig = tracklist[i]->check();

    if(grain_sig == 1 || grain_sig == 3) {
      // Grain is (coming) online
      activeGrains.push_back(tracklist[i]);
    } else if(grain_sig == 2) {
      // Grain is scheduled for deletion
      delete tracklist[i];
      tracklist.erase(tracklist.begin() + i);
      // Handle loop administration
      tracklist_size -= 1;
      i -= 1;
    }
  }

  // Write the current sample on the input line to the internal processing buffer
  if(!_freeze) {
    buffer->write(input->getCurrentSample());
  } else {
    // TODO: somehow figure out which current grains are relevant for looping
    //    -> look at internal position vs envelope mayhaps? ignore if already in decay?
    activeGrains[0]->loop();
  }

  double smp[2] = {0.0, 0.0};

  if(!activeGrains.empty()) {
    for(auto & activeGrain : activeGrains) {
      // TODO: implement envelope
      //    -> switch case: linear / exponential
      smp[0] += activeGrain->process(env_length, env_shape, stereo)[0];
      smp[1] += activeGrain->process(env_length, env_shape, stereo)[1];
    }

    smp[0] = smp[0] * pow(0.99, activeGrains.size());
    smp[1] = smp[1] * pow(0.99, activeGrains.size());

    if(smp[0] > 1.0) {
      smp[0] = 1.0;
    }
    if(smp[1] > 1.0) {
      smp[1] = 1.0;
    }
  }

  // === GRANULAR STRATEGY ===
  // Check for samples to write to output
  //
  // TODO: grains with output have flag and internal check?
  //    ->  central Processor doesn't need to check what grains can be played
  //        only checks for grains that are already marked available
  //    ...or Processor checks every grain?
  //
  // TODO: in freeze mode, Processor stays on the same Grain and loops it
  //    -> position and size impact the Grain directly
  //
  // === END OF STRATEGY ===

  outputL->write(smp[0]);
  outputR->write(smp[1]);
}

void GrainProcess::processParameterChanges(float nSpread, float nSize, float nShape, float nSpeed) {
  // Store readouts
  spread = nSpread;
  size = nSize;
  shape = nShape;
  speed = nSpeed;

  // Map readouts
  performMapping();

  // Write mapping to grain pool
  for(int i = 0; i < tracklist_size; i++) {
    if((i * divisionLen) < length) {
      // Check if the new values fit within the bounds of the buffer
      tracklist[i]->setLength(grainLen);
      tracklist[i]->calculateStart(divisionLen);
    } else {
      // Schedule the grain for deletion
      tracklist[i]->scheduleCleanup();
    }
  }

  //
  if(tracklist_size < nGrains) {
    for(int i = 0; i < nGrains - tracklist_size; i++) {
      tracklist.push_back(new Grain(tracklist_size + i, grainLen, (tracklist_size + i) * divisionLen, buffer));
    }
    tracklist_size = tracklist.size();
  }
}

void GrainProcess::tick() {
  position++;
  buffer->tick();
}

void GrainProcess::freeze() {
  _freeze = !_freeze;
}

// Inline functions
void GrainProcess::performMapping() {
  // Spread: 0 = wide but linear, 511 = smooth (buff len / grain len), 1023 = wide with random
  if(spread < 0.5) {
    int max_grains = 100;
    nGrains = (int) (max_grains * (1.0 - spread) + 2);

    // Calculate division length
    divisionLen = (int) (length / nGrains);
  } else if(spread == 512) {
    nGrains = 1;
    grainLen = length;
    divisionLen = length;
  } else {
    if(random() < spread - 0.5) {
      // Something random happens
    }
  }

  // Size: 0 = tiny grains, 960 = full grains, 960-1023 = random sizes
  if(size < 0.7) {
    // TODO: find ideal max buffer length, for now we use 1/10 samplerate
    // TODO: maybe use exponential with size/maxSize for multiplier? more control for finer grains

    // Size divided by halfway point, anything over halfway is division overrun
    grainLen = (int) (divisionLen * (size / 0.5));
  } else if(size < 0.85) {
    // Randomize, value > division

    // Use default buffer length as placeholder for other MATHS, but set randomizer flag
    grainLen = length;
    rGrainLen = true;
  } else {
    // Randomize, value < division * 1.5
  }

  // Handle... the rest?
  // Shape: 0 = linear @ length/2, 511 = no envelope, 1023 = exponential @ length/2
  if(shape < 0.5) {
    // Set linear shape
    env_shape = 0;
    // set length
    env_length = 0.5f - shape;
  } else {
    // Set exponential shape
    env_shape = 1;
    env_length = 0.5f - (shape - 0.5f);
  }
}

void GrainProcess::setSpread(int nSpread) {
  processParameterChanges(nSpread, size, shape, speed);
}

void GrainProcess::setSize(int nSize) {
  processParameterChanges(spread, nSize, shape, speed);
}

void GrainProcess::setShape(int nShape) {
  processParameterChanges(spread, size, nShape, speed);
}

void GrainProcess::setStereo(int nStereo) {
  stereo = nStereo / 1023.0;
}