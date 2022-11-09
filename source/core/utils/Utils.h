#pragma once

#include "FastNoiseLite/FastNoiseLite.h"

namespace Utils {
    static FastNoiseLite Noise;

    static float RandomRange(float min, float max);
}