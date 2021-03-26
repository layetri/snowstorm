//
// Created by Daniël Kamp on 17/02/2021.
//

#ifndef SNOWSTORM_BUFFER_H
#define SNOWSTORM_BUFFER_H

class Buffer {
public:
    Buffer(int length);
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
};

#endif //SNOWSTORM_BUFFER_H
