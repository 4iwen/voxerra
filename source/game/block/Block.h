#include "BlockType.h"

class Block {
public:
    Block(BlockType type);

    BlockType GetType();

private:
    BlockType _blockType;
};