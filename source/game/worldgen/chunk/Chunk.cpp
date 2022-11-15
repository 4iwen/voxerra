#include "Chunk.h"

#define CHUNK_SIZE 32
#define CHUNK_HEIGHT 512
#define BLOCK_SIZE 1.0f

BlockType chunkData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]{(BlockType)(0)};

Chunk::Chunk(int x, int z) {
    chunkX = x;
    chunkZ = z;

    vao = VertexArray();
    vbo = VertexBuffer();
    ebo = ElementBuffer();
}

void Chunk::Generate() {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            int height = Utils::noise.GetNoise((float) (x + chunkX * CHUNK_SIZE),
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
    glm::vec3 color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 1)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 1)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddRightSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 1)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 1)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddTopSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(chunkData[x][y][z]);


    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 1)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 1)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddBottomSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 1)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 1)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddFrontSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(chunkData[x][y][z]);

    Vertex v1((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 0, 0)) * BLOCK_SIZE, color);
    Vertex v2((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 1, 0)) * BLOCK_SIZE, color);
    Vertex v3((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(1, 0, 0)) * BLOCK_SIZE, color);
    Vertex v4((glm::vec3(x + chunkX * CHUNK_SIZE, y, z + chunkZ * CHUNK_SIZE) + glm::vec3(0, 1, 0)) * BLOCK_SIZE, color);

    AddVertices(v1, v2, v3, v4);
    AddIndices();
}

void Chunk::AddBackSide(int x, int y, int z) {
    glm::vec3 color = GetBlockColor(chunkData[x][y][z]);

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

glm::vec3 Chunk::GetBlockColor(BlockType type) {
    switch (type) {
        case BlockType::GRASS:
            return {0.0f, 1.0f, 0.0f};
        case BlockType::DIRT:
            return {0.5f, 0.35f, 0.05f};
        case BlockType::STONE:
            return {0.5f, 0.5f, 0.5f};
        case BlockType::WATER:
            return {0.0f, 0.0f, 1.0f};
        case BlockType::SAND:
            return {1.0f, 0.9f, 0.0f};
        default:
            return {0.0f, 0.0f, 0.0f};
    }
}

void Chunk::Draw() {
    vao.Bind();
    vbo.Bind();
    vbo.SetData(vertices.data(), vertices.size() * sizeof(float));
    ebo.Bind();
    ebo.SetData(indices.data(), indices.size() * sizeof(unsigned int));
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
