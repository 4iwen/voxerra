#include <iostream>
#include <Math>
#include "Chunk.h"

Chunk::Chunk(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;

    FillBlocksWithAir();
}
void Chunk::FillBlocksWithAir()
{
    for (int x = 0; x < CHUNK_WIDTH; x++)
    {
        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int z = 0; z < CHUNK_LENGTH; z++)
            {
                blockData[x][y][z] = blockType::AIR;
            }
        }
    }
}

glm::vec2 Chunk::getPos()
{
    return glm::vec2(posX, posY);
}

void Chunk::GenerateNoise(FastNoiseLite noise)
{
    for (int x = 0; x < CHUNK_WIDTH; x++)
    {
        for (int z = 0; z < CHUNK_LENGTH; z++) {
            int y = GenerateHeight(x,z);
            for (int i = y; i >= 0; i--)
            {
                if(i > y - 2)
                {
                    blockData[x][i][z] = blockType::GRASS;
                }
                else if(i > y -6)
                {
                    blockData[x][i][z] = blockType::DIRT;
                }
                else
                {
                    blockData[x][i][z] = blockType::STONE;
                }
            }
        }
    }
    GenerateMesh();
}

int Chunk::GenerateHeight(int x, int z)
{
    int base = noise.GetNoise((float)(x + posX * CHUNK_WIDTH),(float)(z + posY * CHUNK_LENGTH)) * 20;

    return std::clamp(base,0,CHUNK_HEIGHT);
}

void Chunk::GenerateMesh()
{
    mesh.vertices.clear();
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_LENGTH; z++) {
                if (blockData[x][y][z] != blockType::AIR) {
                    if(x + 1 >= CHUNK_WIDTH || CheckForBlock(x + 1,y,z))
                        ADD_RIGHT_SIDE(x,y,z);

                    if(x <= 0 || CheckForBlock(x - 1,y,z))
                        ADD_LEFT_SIDE(x,y,z);

                    if(CheckForBlock(x,y + 1,z))
                        ADD_TOP_SIDE(x,y,z);

                    if(y < 0 || CheckForBlock(x,y - 1,z))
                        ADD_BOTTOM_SIDE(x,y,z);

                    if(z + 1 >= CHUNK_LENGTH ||CheckForBlock(x,y,z + 1))
                        ADD_FRONT_SIDE(x,y,z);

                    if(z - 1 < 0 || CheckForBlock(x,y,z - 1))
                        ADD_BACK_SIDE(x,y,z);
                }
            }
        }
    }
}

glm::vec3 Chunk::PICK_BLOCK_COLOR(blockType type)
{
    switch (type)
    {
        case blockType::GRASS:
            return glm::vec3(0,1,0);
        case blockType::DIRT:
            return glm::vec3(0.5,0.5,0);
        case blockType::STONE:
            return glm::vec3(0.5,0.5,0.5);
        default:
            return glm::vec3(0,0,0);
    }
}

void Chunk::ADD_LEFT_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    ADD_INDI_SIDE();
}
void Chunk::ADD_RIGHT_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    ADD_INDI_SIDE();
}
void Chunk::ADD_TOP_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    ADD_INDI_SIDE();
}
void Chunk::ADD_BOTTOM_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    ADD_INDI_SIDE();
}
void Chunk::ADD_FRONT_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    ADD_INDI_SIDE();
}
void Chunk::ADD_BACK_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);
    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_WIDTH) ,y,z + (posY * CHUNK_LENGTH)),color));
    ADD_INDI_SIDE();
}

bool Chunk::CheckForBlock(int x, int y, int z)
{
    return blockData[x][y][z] == blockType::AIR;
}

void Chunk::GENERATE_GL_VERTS() {
    floatVertices.clear();
    for (int i = 0; i < vertices.size(); i++) {
        floatVertices.push_back(vertices[i].Position.x + (posX * CHUNK_WIDTH));
        floatVertices.push_back(vertices[i].Position.y);
        floatVertices.push_back(vertices[i].Position.z + (posY * CHUNK_LENGTH));
        floatVertices.push_back(vertices[i].Color.r);
        floatVertices.push_back(vertices[i].Color.g);
        floatVertices.push_back(vertices[i].Color.b);
    }
}

void Chunk::ADD_INDI_SIDE()
{
    indices.push_back(vertices.size() - 4);
    indices.push_back(vertices.size() - 3);
    indices.push_back(vertices.size() - 2);

    indices.push_back(vertices.size() - 4);
    indices.push_back(vertices.size() - 2);
    indices.push_back(vertices.size() - 1);
}

void Chunk::DrawChunk(Shader shader)
{
    mesh.Draw(shader);
}
