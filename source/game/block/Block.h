#include "BlockType.h"
#include "glm/vec3.hpp"

class Block {
public:
    BlockType GetType();

private:
    BlockType blockType;
    glm::vec3 _color;
};