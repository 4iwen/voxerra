#include "chunk.h"

#define CHUNK_SIZE 32
#define CHUNK_HEIGHT 512
#define BLOCK_SIZE 1.0f

BlockType chunkData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]{(BlockType) (0)};

Chunk::Chunk(int x, int z) {
    chunkX = x;
    chunkZ = z;
    mesh = Mesh();
}

void Chunk::generate() {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            int height = Utils::s_noise.GetNoise((float) (x + chunkX * CHUNK_SIZE),
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

void Chunk::generateVerticesAndIndices() {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (chunkData[x][y][z] == BlockType::AIR) {
                    continue;
                }

                if (x == 0 || chunkData[x - 1][y][z] == BlockType::AIR) {
                    addLeftSide(x, y, z);
                }
                if (x == CHUNK_SIZE - 1 || chunkData[x + 1][y][z] == BlockType::AIR) {
                    addRightSide(x, y, z);
                }
                if (y == 0 || chunkData[x][y - 1][z] == BlockType::AIR) {
                    addBottomSide(x, y, z);
                }
                if (y == CHUNK_HEIGHT - 1 || chunkData[x][y + 1][z] == BlockType::AIR) {
                    addTopSide(x, y, z);
                }
                if (z == 0 || chunkData[x][y][z - 1] == BlockType::AIR) {
                    addFrontSide(x, y, z);
                }
                if (z == CHUNK_SIZE - 1 || chunkData[x][y][z + 1] == BlockType::AIR) {
                    addBackSide(x, y, z);
                }
            }
        }
    }
}

void Chunk::addLeftSide(int x, int y, int z) {
    glm::vec3 color = Utils::getBlockColor(chunkData[x][y][z]);

    Vertex v1{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 1)) * BLOCK_SIZE,
              color};
    Vertex v2{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE,
              color};
    Vertex v3{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE,
              color};
    Vertex v4{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 1)) * BLOCK_SIZE,
              color};

    mesh.addVertices(v1, v2, v3, v4);
    mesh.addIndices();
}

void Chunk::addRightSide(int x, int y, int z) {
    glm::vec3 color = Utils::getBlockColor(chunkData[x][y][z]);

    Vertex v1{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE,
              color};
    Vertex v2{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 1)) * BLOCK_SIZE,
              color};
    Vertex v3{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 1)) * BLOCK_SIZE,
              color};
    Vertex v4{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE,
              color};

    mesh.addVertices(v1, v2, v3, v4);
    mesh.addIndices();
}

void Chunk::addTopSide(int x, int y, int z) {
    glm::vec3 color = Utils::getBlockColor(chunkData[x][y][z]);

    Vertex v1{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE,
              color};
    Vertex v2{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 1)) * BLOCK_SIZE,
              color};
    Vertex v3{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 1)) * BLOCK_SIZE,
              color};
    Vertex v4{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE,
              color};

    mesh.addVertices(v1, v2, v3, v4);
    mesh.addIndices();
}

void Chunk::addBottomSide(int x, int y, int z) {
    glm::vec3 color = Utils::getBlockColor(chunkData[x][y][z]);

    Vertex v1{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 1)) * BLOCK_SIZE,
              color};
    Vertex v2{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE,
              color};
    Vertex v3{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 1)) * BLOCK_SIZE,
              color};
    Vertex v4{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE,
              color};

    mesh.addVertices(v1, v2, v3, v4);
    mesh.addIndices();
}

void Chunk::addFrontSide(int x, int y, int z) {
    glm::vec3 color = Utils::getBlockColor(chunkData[x][y][z]);

    Vertex v1{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE,
              color};
    Vertex v2{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE,
              color};
    Vertex v3{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE,
              color};
    Vertex v4{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE,
              color};

    mesh.addVertices(v1, v2, v3, v4);
    mesh.addIndices();
}

void Chunk::addBackSide(int x, int y, int z) {
    glm::vec3 color = Utils::getBlockColor(chunkData[x][y][z]);

    Vertex v1{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 1)) * BLOCK_SIZE,
              color};
    Vertex v2{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 1)) * BLOCK_SIZE,
              color};
    Vertex v3{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 1)) * BLOCK_SIZE,
              color};
    Vertex v4{(glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 1)) * BLOCK_SIZE,
              color};

    mesh.addVertices(v1, v2, v3, v4);
    mesh.addIndices();
}

void Chunk::draw() {
    mesh.draw();
}
