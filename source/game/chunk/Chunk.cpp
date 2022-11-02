#include "Chunk.h"

Chunk::Chunk(int x, int z)
{
    _x = x;
    _z = z;
}

Chunk::~Chunk()
{
    // TODO: delete chunk?
}

void Chunk::Generate()
{

}

Block Chunk::GetBlock(int x, int y, int z)
{
    return _chunkData[x][y][z];
}

void Chunk::SetBlock(int x, int y, int z, Block block)
{
    _chunkData[x][y][z] = block;
}