#include "Utils.h"

float Utils::RandomRangeF(float min, float max)  {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

glm::vec3 Utils::GetBlockColor(BlockType type)  {
    switch (type) {
        case BlockType::GRASS:
            return {0.0f, 1.0f, 0.0f};
        case BlockType::DIRT:
            return {0.5f, 0.35f, 0.05f};
        case BlockType::STONE:
            return {0.5f, 0.5f, 0.5f};
        case BlockType::WATER:
            return {0.0f, 0.0f, 1.0f};
        case BlockType::SAND:
            return {1.0f, 0.9f, 0.0f};
        default:
            return {0.0f, 0.0f, 0.0f};
    }
}