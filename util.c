#include "include/econsim.h"

int randrange(int min, int max) {
    if (max == min)
        return max;

    return (rand() % (max - min)) + min;
}

float randfrange(float min, float max) {
    if (min == max)
        return min;

    float diff = max - min;
    float x = (float) rand() / ((float) RAND_MAX / diff);
    return x + min;
}
