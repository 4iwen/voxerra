#pragma once

#include "FastNoiseLite/FastNoiseLite.h"
#include "glm/vec3.hpp"
#include "../../game/block/BlockType.h"

namespace Utils {
    static FastNoiseLite noise;

    float RandomRangeF(float min, float max);
    glm::vec3 GetBlockColor(BlockType type);
}