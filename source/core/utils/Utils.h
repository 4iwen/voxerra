#pragma once

#include "FastNoiseLite/FastNoiseLite.h"

namespace Utils {
    static FastNoiseLite Noise(1337);

    static float RandomRange(float min, float max) {
        return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    }
}