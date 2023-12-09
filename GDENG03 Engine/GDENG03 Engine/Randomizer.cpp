#include"Randomizer.h"
#include<stdlib.h>

int Randomizer::getRandomInteger(int inclusive_minimum, int inclusive_maximum) {
    int range = inclusive_maximum - inclusive_minimum + 1;
    int randomInt = inclusive_minimum + (rand() % range);

    return randomInt;
}

float Randomizer::getRandomFloat(float inclusive_minimum, float inclusive_maximum) {
    float randomFactor = ((float)rand()) / (float)RAND_MAX;
    float range = inclusive_maximum - inclusive_minimum;
    float randomFloat = inclusive_minimum + (randomFactor * range);

    return randomFloat;
}