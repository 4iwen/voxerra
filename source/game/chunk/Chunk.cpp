#include "Chunk.h"

#define CHUNK_SIZE 32
#define CHUNK_HEIGHT 512
#define BLOCK_SIZE 1.0f

BlockType chunkData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]{static_cast<BlockType>(0)};

Chunk::Chunk(int x, int z) {
    chunkX = x;
    chunkZ = z;
}

void Chunk::Generate() {
    // "Cube World" game-like terrain generation
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFrequency(0.01f);
    noise.SetFractalOctaves(4);
    noise.SetFractalLacunarity(2.0f);
    noise.SetFractalGain(0.5f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Euclidean);
    noise.SetCellularReturnType(FastNoiseLite::CellularReturnType_Distance2Div);
    noise.SetCellularJitter(0.45f);

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            int height = Utils::Noise.GetNoise((float) (x + chunkX * CHUNK_SIZE),
                                               (float) (z + chunkZ * CHUNK_SIZE)) * 20;
            height += 10;
            if (height < 0)
                height = 0;
            chunkData[x][height][z] = BlockType::GRASS;
            for (int i = height - 1; i >= 0; i--) {
                if (i > height - 5) {
                    chunkData[x][i][z] = BlockType::DIRT;
                } else {
                    chunkData[x][i][z] = BlockType::STONE;
                }
            }
        }
    }
}

void Chunk::GenerateVerticesAndIndices() {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (chunkData[x][y][z]== BlockType::AIR) {
                    continue;
                }

                if (x == 0 || chunkData[x - 1][y][z] == BlockType::AIR) {
                    AddLeftSide(x, y, z);
                }
                if (x == CHUNK_SIZE - 1 || chunkData[x + 1][y][z] == BlockType::AIR) {
                    AddRightSide(x, y, z);
                }
                if (y == 0 || chunkData[x][y - 1][z] == BlockType::AIR) {
                    AddBottomSide(x, y, z);
                }
                if (y == CHUNK_HEIGHT - 1 || chunkData[x][y + 1][z] == BlockType::AIR) {
                    AddTopSide(x, y, z);
                }
                if (z == 0 || chunkData[x][y][z - 1] == BlockType::AIR) {
                    AddFrontSide(x, y, z);
                }
                if (z == CHUNK_SIZE - 1 || chunkData[x][y][z + 1] == BlockType::AIR) {
                    AddBackSide(x, y, z);
                }
            }
        }
    }
}

void Chunk::GetVertices(std::vector<float> &vertices) {
    vertices = this->vertices;
}

void Chunk::GetIndices(std::vector<unsigned int> &indices) {
    indices = this->indices;
}

void Chunk::AddLeftSide(int x, int y, int z) {
    BlockColor color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 1)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 1)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddRightSide(int x, int y, int z) {
    BlockColor color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 1)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 1)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddTopSide(int x, int y, int z) {
    BlockColor color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 1)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 1)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddBottomSide(int x, int y, int z) {
    BlockColor color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 1)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 1)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddFrontSide(int x, int y, int z) {
    BlockColor color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddBackSide(int x, int y, int z) {
    BlockColor color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 1)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 1)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 1)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 1)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddVertices(Vertex vertex, Vertex vertex1, Vertex vertex2, Vertex vertex3) {
    vertices.push_back(vertex.position.x);
    vertices.push_back(vertex.position.y);
    vertices.push_back(vertex.position.z);
    vertices.push_back(vertex.color.r);
    vertices.push_back(vertex.color.g);
    vertices.push_back(vertex.color.b);

    vertices.push_back(vertex1.position.x);
    vertices.push_back(vertex1.position.y);
    vertices.push_back(vertex1.position.z);
    vertices.push_back(vertex1.color.r);
    vertices.push_back(vertex1.color.g);
    vertices.push_back(vertex1.color.b);

    vertices.push_back(vertex2.position.x);
    vertices.push_back(vertex2.position.y);
    vertices.push_back(vertex2.position.z);
    vertices.push_back(vertex2.color.r);
    vertices.push_back(vertex2.color.g);
    vertices.push_back(vertex2.color.b);

    vertices.push_back(vertex3.position.x);
    vertices.push_back(vertex3.position.y);
    vertices.push_back(vertex3.position.z);
    vertices.push_back(vertex3.color.r);
    vertices.push_back(vertex3.color.g);
    vertices.push_back(vertex3.color.b);
}

void Chunk::AddIndices() {
    indices.push_back(indicesIndex);
    indices.push_back(indicesIndex + 1);
    indices.push_back(indicesIndex + 2);
    indices.push_back(indicesIndex);
    indices.push_back(indicesIndex + 3);
    indices.push_back(indicesIndex + 1);
    indicesIndex += 4;
}

BlockColor Chunk::GetBlockColor(BlockType type) {
    BlockColor color{};

    switch (type) {
        case BlockType::GRASS:
            color.r = 0.0f;
            color.g = 1.0f;
            color.b = 0.0f;
            break;
        case BlockType::DIRT:
            color.r = 0.5f;
            color.g = 0.35f;
            color.b = 0.05f;
            break;
        case BlockType::STONE:
            color.r = 0.5f;
            color.g = 0.5f;
            color.b = 0.5f;
            break;
        case BlockType::WATER:
            color.r = 0.0f;
            color.g = 0.0f;
            color.b = 1.0f;
            break;
        case BlockType::SAND:
            color.r = 1.0f;
            color.g = 0.9f;
            color.b = 0.0f;
            break;
        default:
            color.r = 0.0f;
            color.g = 0.0f;
            color.b = 0.0f;
            break;
    }

    return color;
}
