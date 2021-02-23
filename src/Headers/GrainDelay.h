//
// Created by Daniël Kamp on 12/02/2021.
//

#ifndef SNOWSTORM_GRAINDELAY_H
#define SNOWSTORM_GRAINDELAY_H
#include "Grain.h"

class GrainDelay {
public:
    GrainDelay();
    virtual ~GrainDelay();

    Grain *const *getTimeline() const;
    Grain readTimeline(int position);
    void tick();

private:
    Grain* timeline[40];
};


#endif //SNOWSTORM_GRAINDELAY_H
