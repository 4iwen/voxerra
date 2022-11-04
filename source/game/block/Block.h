#include "BlockType.h"
#include "glm/vec3.hpp"

class Block {
public:
    BlockType GetType();

    void SetType(BlockType type);

private:
    BlockType blockType;
};