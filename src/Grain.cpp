//
// Created by Daniël Kamp on 12/02/2021.
//

#include "Headers/Grain.h"

using namespace std;

Grain::Grain(Buffer *buffer) {
  length = buffer->getSize();
  active = false;
  random = false;
  position = 0;
  sample = 0.0;
}

Grain::~Grain() {

}
