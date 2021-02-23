//
// Created by Daniël Kamp on 17/02/2021.
//

#ifndef SNOWSTORM_BUFFER_H
#define SNOWSTORM_BUFFER_H


class Buffer {
public:
    Buffer(int length);
    ~Buffer();

    int getSize();
    float getSample(int sample_position);
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
