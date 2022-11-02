#include "Block.h"

Block::Block(BlockType type)
{
    _blockType = type;
}

BlockType Block::GetType() {
    return _blockType;
}