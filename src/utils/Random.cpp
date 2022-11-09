//
// Created by 42077 on 9/27/2022.
//

#include "Random.h"
#include <cstdlib>

float Random::Range(int min, int max) {
    return rand() % max / min;
}
