#include <iostream>
#include "Chunk.h"

Chunk::Chunk(int posX, int posZ, FastNoiseLite noise)
{
    this->posX = posX;
    this->posZ = posZ;
    this->noise = noise;

    FillBlocksWithAir();
}
void Chunk::FillBlocksWithAir()
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                blockData[x][y][z] = blockType::AIR;
            }
        }
    }
}

glm::vec2 Chunk::getPos()
{
    return glm::vec2(posX, posZ);
}

void Chunk::GenerateNoise()
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++) {
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
}

int Chunk::GenerateHeight(int x, int z)
{
    int base = noise.GetNoise((float)(x + posX * CHUNK_SIZE),(float)(z + posZ * CHUNK_SIZE)) * 20;

    return std::clamp(base,0,CHUNK_HEIGHT);
}

void Chunk::GenerateMesh()
{
    mesh.vertices.clear();
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (blockData[x][y][z] != blockType::AIR) {
                    if(x + 1 >= CHUNK_SIZE || CheckForBlock(x + 1,y,z))
                        AddVertex(0,x,y,z);

                    if(x <= 0 || CheckForBlock(x - 1,y,z))
                        AddVertex(1,x,y,z);

                    if(CheckForBlock(x,y + 1,z))
                        AddVertex(2,x,y,z);

                    if(y < 0 || CheckForBlock(x,y - 1,z))
                        AddVertex(3,x,y,z);

                    if(z + 1 >= CHUNK_SIZE ||CheckForBlock(x,y,z + 1))
                        AddVertex(4,x,y,z);

                    if(z - 1 < 0 || CheckForBlock(x,y,z - 1))
                        AddVertex(5,x,y,z);
                }
            }
        }
    }
}

glm::vec3 Chunk::ColorPicker(blockType type)
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

void Chunk::AddVertex(int face,int x, int y, int z)
{
    glm::vec3 color = ColorPicker(blockData[x][y][z]);

    for (int i = 0; i < 4; ++i) {
        mesh.vertices.push_back(Vertex(vertex_positions[face][i] + glm::vec3(x + (posX * CHUNK_SIZE),y,z+ (posZ * CHUNK_SIZE)), color));
    }
}

//void Chunk::ADD_LEFT_SIDE(int x, int y, int z)
//{
//    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);
//
//    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    ADD_INDI_SIDE();
//}
//void Chunk::ADD_RIGHT_SIDE(int x, int y, int z)
//{
//    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);
//
//    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    ADD_INDI_SIDE();
//}
//void Chunk::ADD_TOP_SIDE(int x, int y, int z)
//{
//    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);
//
//    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    ADD_INDI_SIDE();
//}
//void Chunk::ADD_BOTTOM_SIDE(int x, int y, int z)
//{
//    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);
//
//    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    ADD_INDI_SIDE();
//}
//void Chunk::ADD_FRONT_SIDE(int x, int y, int z)
//{
//    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);
//
//    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_FRONT_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    ADD_INDI_SIDE();
//}
//void Chunk::ADD_BACK_SIDE(int x, int y, int z)
//{
//    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);
//    mesh.vertices.push_back(Vertex(vert::LEFT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::LEFT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_BOTTOM_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    mesh.vertices.push_back(Vertex(vert::RIGHT_TOP_BACK_CORNER +  glm::vec3(x + (posX * CHUNK_SIZE) ,y,z + (posY * CHUNK_SIZE)),color));
//    ADD_INDI_SIDE();
//}

bool Chunk::CheckForBlock(int x, int y, int z)
{
    return blockData[x][y][z] == blockType::AIR;
}

void Chunk::DrawChunk(Shader shader)
{
    mesh.Draw(shader);
}

bool Chunk::isChunkInRenderDistance(float d, float d1, int i) {
    if(d > (posX * CHUNK_SIZE) - i && d < (posX * CHUNK_SIZE) + i)
    {
        if(d1 > (posZ * CHUNK_SIZE) - i && d1 < (posZ * CHUNK_SIZE) + i)
        {
            return true;
        }
    }
}
