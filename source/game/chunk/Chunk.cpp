#include "Chunk.h"

Chunk::Chunk(int x, int z) {
    _x = x;
    _z = z;
}

Chunk::~Chunk() {
    // TODO: delete chunk?
}

void Chunk::Generate() {
    Utils::Noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    Utils::Noise.SetFrequency(0.01f);
    Utils::Noise.SetFractalOctaves(5);
    Utils::Noise.SetFractalLacunarity(2.0f);
    Utils::Noise.SetFractalGain(0.5f);
    Utils::Noise.SetFractalType(FastNoiseLite::FractalType_FBm);

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            int height = (int) (Utils::Noise.GetNoise((float) (x + _x * CHUNK_SIZE),
                                                      (float) (z + _z * CHUNK_SIZE)) * 10.0f);
            for (int y = 0; y < CHUNK_SIZE; y++) {
                if (y == height) {
                    _chunkData[x][y][z] = BlockType::GRASS;
                } else if (y < height) {
                    _chunkData[x][y][z] = BlockType::DIRT;
                } else {
                    _chunkData[x][y][z] = BlockType::AIR;
                }
            }
        }
    }
}

// generate vertices for chunk, every block will have 36 vertices and 36 indices
// 36 vertices and 36 indices are generated for every block, except if the block is air
// this is because air blocks don't need to be rendered
// the vertices and indices are stored in the vertices and indices vectors
void Chunk::GenerateVerticesAndIndices() {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (_chunkData[x][y][z] != BlockType::AIR) {
                    // front face
                    if (_chunkData[x][y][z - 1] == BlockType::AIR) {
                        // top left
                        vertices.push_back(x);
                        vertices.push_back(y + 1);
                        vertices.push_back(z);
                        // bottom left
                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z);
                        // bottom right
                        vertices.push_back(x + 1);
                        vertices.push_back(y);
                        vertices.push_back(z);
                        // top right
                        vertices.push_back(x + 1);
                        vertices.push_back(y + 1);
                        vertices.push_back(z);
                    }
                    // back face
                    if (_chunkData[x][y][z + 1] == BlockType::AIR) {
                        // top left
                        vertices.push_back(x);
                        vertices.push_back(y + 1);
                        vertices.push_back(z + 1);
                        // bottom left
                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z + 1);
                        // bottom right
                        vertices.push_back(x + 1);
                        vertices.push_back(y);
                        vertices.push_back(z + 1);
                        // top right
                        vertices.push_back(x + 1);
                        vertices.push_back(y + 1);
                        vertices.push_back(z + 1);
                    }
                    // top face
                    if (_chunkData[x][y + 1][z] == BlockType::AIR) {
                        // top left
                        vertices.push_back(x);
                        vertices.push_back(y + 1);
                        vertices.push_back(z);
                        // bottom left
                        vertices.push_back(x);
                        vertices.push_back(y + 1);
                        vertices.push_back(z + 1);
                        // bottom right
                        vertices.push_back(x + 1);
                        vertices.push_back(y + 1);
                        vertices.push_back(z + 1);
                        // top right
                        vertices.push_back(x + 1);
                        vertices.push_back(y + 1);
                        vertices.push_back(z);
                    }
                    // bottom face
                    if (_chunkData[x][y - 1][z] == BlockType::AIR) {
                        // top left
                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z);
                        // bottom left
                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z + 1);
                        // bottom right
                        vertices.push_back(x + 1);
                        vertices.push_back(y);
                        vertices.push_back(z + 1);
                        // top right
                        vertices.push_back(x + 1);
                        vertices.push_back(y);
                        vertices.push_back(z);
                    }
                    // left face
                    if (_chunkData[x - 1][y][z] == BlockType::AIR) {
                        // top left
                        vertices.push_back(x);
                        vertices.push_back(y + 1);
                        vertices.push_back(z);
                        // bottom left
                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z);
                        // bottom right
                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z + 1);
                        // top right
                        vertices.push_back(x);
                        vertices.push_back(y + 1);
                        vertices.push_back(z + 1);
                    }
                    // right face
                    if (_chunkData[x + 1][y][z] == BlockType::AIR) {
                        // top left
                        vertices.push_back(x + 1);
                        vertices.push_back(y + 1);
                        vertices.push_back(z);
                        // bottom left
                        vertices.push_back(x + 1);
                        vertices.push_back(y);
                        vertices.push_back(z);
                        // bottom right
                        vertices.push_back(x + 1);
                        vertices.push_back(y);
                        vertices.push_back(z + 1);
                        // top right
                        vertices.push_back(x + 1);
                        vertices.push_back(y + 1);
                        vertices.push_back(z + 1);
                    }

                    // generate indices for the above vertices
                    for (int i = 0; i < 6; i++) {
                        indices.push_back((i * 4) + 0);
                        indices.push_back((i * 4) + 1);
                        indices.push_back((i * 4) + 2);
                        indices.push_back((i * 4) + 0);
                        indices.push_back((i * 4) + 2);
                        indices.push_back((i * 4) + 3);
                    }
                }
            }
        }
    }
}

Block Chunk::GetBlock(int x, int y, int z) {
    return _chunkData[x][y][z];
}

void Chunk::SetBlock(int x, int y, int z, BlockType type) {
    _chunkData[x][y][z] = type;
}

void Chunk::GetVertices(std::vector<float> &vertices) {
    vertices = this->vertices;
}

void Chunk::GetIndices(std::vector<unsigned int> &indices) {
    indices = this->indices;
}


