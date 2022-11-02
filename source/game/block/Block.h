#include "BlockType.h"
#include "glm/glm.hpp"

class Block
{
public:
    Block();

private:
    BlockType _blockType;
    glm::vec3 _position;
};