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
    Utils::Noise.SetFractalOctaves(2);
    Utils::Noise.SetFractalLacunarity(2.0f);
    Utils::Noise.SetFractalGain(0.5f);
    Utils::Noise.SetFractalType(FastNoiseLite::FractalType_Ridged);

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                _chunkData[x][y][z].SetType(BlockType::AIR);
            }
        }
    }

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            int y = Utils::Noise.GetNoise((float) (x + _x * CHUNK_SIZE), (float) (z + _z * CHUNK_SIZE)) * 20;
            _chunkData[x][y][z].SetType(BlockType::GRASS);
            for (int i = y - 1; i > 0; i--) {
                if (i > y - 5) {
                    _chunkData[x][i][z].SetType(BlockType::DIRT);
                } else {
                    _chunkData[x][i][z].SetType(BlockType::STONE);
                }
            }
        }
    }
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
                        AddRightSide(x, y, z);
                    if (x <= 0 || GetBlock(x - 1, y, z).GetType() == BlockType::AIR)
                        AddLeftSide(x, y, z);
                    if (y + 1 < CHUNK_HEIGHT || GetBlock(x, y + 1, z).GetType() == BlockType::AIR)
                        AddTopSide(x, y, z);
                    if (y < 0 || GetBlock(x, y - 1, z).GetType() == BlockType::AIR)
                        AddBottomSide(x, y, z);
                    if (z + 1 >= CHUNK_SIZE || GetBlock(x, y, z + 1).GetType() == BlockType::AIR)
                        AddFrontSide(x, y, z);
                    if (z - 1 < 0 || GetBlock(x, y, z - 1).GetType() == BlockType::AIR)
                        AddBackSide(x, y, z);

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

void Chunk::AddLeftSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(_chunkData[x][y][z].GetType());

    Vertex v1(glm::vec3(x, y, z) + glm::vec3(0, 0, 1), color);
    Vertex v2(glm::vec3(x, y, z) + glm::vec3(0, 1, 0), color);
    Vertex v3(glm::vec3(x, y, z) + glm::vec3(0, 0, 0), color);
    Vertex v4(glm::vec3(x, y, z) + glm::vec3(0, 1, 1), color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddRightSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(_chunkData[x][y][z].GetType());

    Vertex v1(glm::vec3(x, y, z) + glm::vec3(1, 0, 0), color);
    Vertex v2(glm::vec3(x, y, z) + glm::vec3(1, 1, 1), color);
    Vertex v3(glm::vec3(x, y, z) + glm::vec3(1, 0, 1), color);
    Vertex v4(glm::vec3(x, y, z) + glm::vec3(1, 1, 0), color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddTopSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(_chunkData[x][y][z].GetType());

    Vertex v1(glm::vec3(x, y, z) + glm::vec3(0, 1, 0), color);
    Vertex v2(glm::vec3(x, y, z) + glm::vec3(1, 1, 1), color);
    Vertex v3(glm::vec3(x, y, z) + glm::vec3(1, 1, 0), color);
    Vertex v4(glm::vec3(x, y, z) + glm::vec3(0, 1, 1), color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddBottomSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(_chunkData[x][y][z].GetType());

    Vertex v1(glm::vec3(x, y, z) + glm::vec3(0, 0, 1), color);
    Vertex v2(glm::vec3(x, y, z) + glm::vec3(1, 0, 0), color);
    Vertex v3(glm::vec3(x, y, z) + glm::vec3(1, 0, 1), color);
    Vertex v4(glm::vec3(x, y, z) + glm::vec3(0, 0, 0), color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddFrontSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(_chunkData[x][y][z].GetType());

    Vertex v1(glm::vec3(x, y, z) + glm::vec3(0, 0, 0), color);
    Vertex v2(glm::vec3(x, y, z) + glm::vec3(1, 1, 0), color);
    Vertex v3(glm::vec3(x, y, z) + glm::vec3(1, 0, 0), color);
    Vertex v4(glm::vec3(x, y, z) + glm::vec3(0, 1, 0), color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddBackSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(_chunkData[x][y][z].GetType());

    Vertex v1(glm::vec3(x, y, z) + glm::vec3(0, 1, 1), color);
    Vertex v2(glm::vec3(x, y, z) + glm::vec3(1, 0, 1), color);
    Vertex v3(glm::vec3(x, y, z) + glm::vec3(1, 1, 1), color);
    Vertex v4(glm::vec3(x, y, z) + glm::vec3(0, 0, 1), color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddVertices(Vertex vertex, Vertex vertex1, Vertex vertex2, Vertex vertex3) {
    vertices.push_back(vertex.GetPosition().x);
    vertices.push_back(vertex.GetPosition().y);
    vertices.push_back(vertex.GetPosition().z);
    vertices.push_back(vertex.GetColor().x);
    vertices.push_back(vertex.GetColor().y);
    vertices.push_back(vertex.GetColor().z);

    vertices.push_back(vertex1.GetPosition().x);
    vertices.push_back(vertex1.GetPosition().y);
    vertices.push_back(vertex1.GetPosition().z);
    vertices.push_back(vertex1.GetColor().x);
    vertices.push_back(vertex1.GetColor().y);
    vertices.push_back(vertex1.GetColor().z);

    vertices.push_back(vertex2.GetPosition().x);
    vertices.push_back(vertex2.GetPosition().y);
    vertices.push_back(vertex2.GetPosition().z);
    vertices.push_back(vertex2.GetColor().x);
    vertices.push_back(vertex2.GetColor().y);
    vertices.push_back(vertex2.GetColor().z);

    vertices.push_back(vertex3.GetPosition().x);
    vertices.push_back(vertex3.GetPosition().y);
    vertices.push_back(vertex3.GetPosition().z);
    vertices.push_back(vertex3.GetColor().x);
    vertices.push_back(vertex3.GetColor().y);
    vertices.push_back(vertex3.GetColor().z);
}

glm::vec3 Chunk::GetBlockColor(BlockType type) {
    switch (type) {
        case BlockType::GRASS:
            return glm::vec3(0.0f, 1.0f, 0.0f);
        case BlockType::DIRT:
            return glm::vec3(0.5f, 0.35f, 0.05f);
        case BlockType::STONE:
            return glm::vec3(0.5f, 0.5f, 0.5f);
        default:
            return glm::vec3(0.0f, 0.0f, 0.0f);
    }
}

void Chunk::AddIndices() {
    int size = indices.size();

    indices.push_back(size + 0);
    indices.push_back(size + 1);
    indices.push_back(size + 2);
    indices.push_back(size + 0);
    indices.push_back(size + 3);
    indices.push_back(size + 1);
}