#pragma once

#include "FastNoiseLite/FastNoiseLite.h"
#include "glm/vec3.hpp"
#include "../../game/block/blocktype.h"

namespace Utils {
    static FastNoiseLite s_noise;

    glm::vec3 getBlockColor(BlockType type);
}