#include "Block.h"

BlockType Block::GetType() {
    return blockType;
}

void Block::SetType(BlockType type) {
    blockType = type;
}