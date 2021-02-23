//
// Created by Daniël Kamp on 12/02/2021.
//

#include "Headers/GrainDelay.h"

GrainDelay::GrainDelay() {}

GrainDelay::~GrainDelay() {

}

Grain *const *GrainDelay::getTimeline() const {
  return timeline;
}

Grain GrainDelay::readTimeline(int position) {
  //return timeline[position];
}

void GrainDelay::tick() {

}
