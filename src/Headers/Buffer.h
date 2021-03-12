//
// Created by Daniël Kamp on 17/02/2021.
//

#ifndef SNOWSTORM_BUFFER_H
#define SNOWSTORM_BUFFER_H

#include <string>

class Buffer {
public:
    Buffer(int length, std::string name);
    ~Buffer();

    void write(float sample);
    int getSize();

    int getPosition();

    float getSample(int sample_position);
    float getCurrentSample();
    void tick();

    float& operator[] (int index) {
      return data[index];
    }

private:
    float *data;
    int size;
    int position;
    std::string name;
};

#endif //SNOWSTORM_BUFFER_H
