#pragma once

#include "FastNoiseLite/FastNoiseLite.h"
#include "glm/vec3.hpp"
#include "../../game/block/BlockType.h"

namespace Utils {
    static FastNoiseLite *noise;

    static float RandomRange(float min, float max);

    static glm::vec3 GetBlockColor(BlockType type);
}