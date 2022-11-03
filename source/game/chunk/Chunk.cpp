#include "Chunk.h"

Chunk::Chunk(int x, int z) {
    _x = x;
    _z = z;
}

Chunk::~Chunk() {
    // TODO: delete chunk?
}

void Chunk::Generate() {
}

/*
 * copy code from this
 * https://github.com/4iwen/voxerra/blob/liquid-merge/source/worldgen/chunk.cpp
 * https://github.com/4iwen/voxerra/blob/liquid-merge/source/worldgen/chunk.h
 * https://github.com/4iwen/voxerra/blob/liquid-merge/source/utils/vert.cpp
 * https://github.com/4iwen/voxerra/blob/liquid-merge/source/utils/vert.h
 * https://github.com/4iwen/voxerra/blob/liquid-merge/source/worldgen/block.cpp
 * https://github.com/4iwen/voxerra/blob/liquid-merge/source/worldgen/block.h
*/
void Chunk::GenerateVerticesAndIndices() {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (GetBlock(x, y, z).GetType() != BlockType::AIR) {
                    if (x + 1 >= CHUNK_SIZE || GetBlock(x + 1, y, z).GetType() == BlockType::AIR)
                        //AddRightSide(x, y, z);
                        if (x <= 0 || GetBlock(x - 1, y, z).GetType() == BlockType::AIR)
                            //AddLeftSide(x, y, z);
                            if (y + 1 < CHUNK_HEIGHT || GetBlock(x, y + 1, z).GetType() == BlockType::AIR)
                                //AddTopSide(x, y, z);
                                if (y < 0 || GetBlock(x, y - 1, z).GetType() == BlockType::AIR)
                                    //AddBottomSide(x, y, z);
                                    if (z + 1 >= CHUNK_SIZE || GetBlock(x, y, z + 1).GetType() == BlockType::AIR)
                                        //AddFrontSide(x, y, z);
                                        if (z - 1 < 0 || GetBlock(x, y, z - 1).GetType() == BlockType::AIR)
                                            //AddBackSide(x, y, z);
                                            return;
                }
            }
        }
    }
}

Block Chunk::GetBlock(int x, int y, int z) {
    return _chunkData[x][y][z];
}

void Chunk::SetBlock(int x, int y, int z, Block block) {
    _chunkData[x][y][z] = block;
}

void Chunk::GetVertices(std::vector<float> &vertices) {
    vertices = this->vertices;
}

void Chunk::GetIndices(std::vector<unsigned int> &indices) {
    indices = this->indices;
}


