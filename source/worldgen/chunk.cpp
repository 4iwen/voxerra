#include <iostream>
#include "chunk.h"

chunk::chunk(int width, int height, int length,int posX,int posY, FastNoiseLite noise)
{
    this->width = width;
    this->height = height;
    this->length = length;
    this->posX = posX;
    this->posY = posY;
    this->noise = noise;

    fillBlocksWithAir();
    generateNoise();
    generateVerts();
    GENERATE_GL_VERTS();
}
void chunk::fillBlocksWithAir()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            for (int z = 0; z < length; z++)
            {
                blockData[x][y][z] = blockType::AIR;
            }
        }
    }
}

glm::vec2 chunk::getPos()
{
    return glm::vec2(posX, posY);
}

void chunk::generateNoise()
{
    for (int x = 0; x < width; x++)
    {
        for (int z = 0; z < length; z++) {
            int y = generateHeight(x,z);
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

int chunk::generateHeight(int x, int z)
{
    int base = noise.GetNoise((float)(x + posX * width),(float)(z + posY * length)) * 20;

    return std::clamp(base,0,height);
}

void chunk::generateVerts() 
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < length; z++) {
                if (blockData[x][y][z] != blockType::AIR) {
                    if(x + 1 >= width || checkForBlock(x + 1,y,z))
                        ADD_RIGHT_SIDE(x,y,z);

                    if(x <= 0 || checkForBlock(x - 1,y,z))
                        ADD_LEFT_SIDE(x,y,z);

                    if(checkForBlock(x,y + 1,z))
                        ADD_TOP_SIDE(x,y,z);

                    if(y < 0 || checkForBlock(x,y - 1,z))
                        ADD_BOTTOM_SIDE(x,y,z);

                    if(z + 1 >= length ||checkForBlock(x,y,z + 1))
                        ADD_FRONT_SIDE(x,y,z);

                    if(z - 1 < 0 || checkForBlock(x,y,z - 1))
                        ADD_BACK_SIDE(x,y,z);
                }
            }
        }
    }
}

glm::vec3 chunk::PICK_BLOCK_COLOR(blockType type)
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

void chunk::ADD_LEFT_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    verts.push_back(vert(vert::LEFT_TOP_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::LEFT_TOP_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::LEFT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::LEFT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    ADD_INDI_SIDE();
}
void chunk::ADD_RIGHT_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    verts.push_back(vert(vert::RIGHT_TOP_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_TOP_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    ADD_INDI_SIDE();
}
void chunk::ADD_TOP_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    verts.push_back(vert(vert::LEFT_TOP_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::LEFT_TOP_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_TOP_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_TOP_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    ADD_INDI_SIDE();
}
void chunk::ADD_BOTTOM_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    verts.push_back(vert(vert::LEFT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::LEFT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    ADD_INDI_SIDE();
}
void chunk::ADD_FRONT_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    verts.push_back(vert(vert::LEFT_TOP_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::LEFT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_TOP_FRONT_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    ADD_INDI_SIDE();
}
void chunk::ADD_BACK_SIDE(int x, int y, int z)
{
    glm::vec3 color = PICK_BLOCK_COLOR(blockData[x][y][z]);

    verts.push_back(vert(vert::LEFT_TOP_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::LEFT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    verts.push_back(vert(vert::RIGHT_TOP_BACK_CORNER + glm::vec3(x,y,z),color.r,color.g,color.b));
    ADD_INDI_SIDE();
}

bool chunk::checkForBlock(int x, int y, int z)
{
    return blockData[x][y][z] == blockType::AIR;
}

void chunk::GENERATE_GL_VERTS()
{
    GLverts.clear();
    for (int i = 0; i < verts.size(); i++) {
        GLverts.push_back(verts[i].position.x + (posX * width));
        GLverts.push_back(verts[i].position.y);
        GLverts.push_back(verts[i].position.z + (posY * length));
        GLverts.push_back(verts[i].red);
        GLverts.push_back(verts[i].green);
        GLverts.push_back(verts[i].blue);
    }
}

std::vector<GLfloat>* chunk::getVerts()
{
    return &GLverts;
}

std::vector<GLuint>* chunk::getIndices()
{
    return &indices;
}

int chunk::getVertSize()
{
    GENERATE_GL_VERTS();
    return GLverts.size();
}

int chunk::getIndiceSize()
{
    return indices.size();
}

void chunk::ADD_INDI_SIDE()
{
    indices.push_back(verts.size() - 4);
    indices.push_back(verts.size() - 3);
    indices.push_back(verts.size() - 2);

    indices.push_back(verts.size() - 4);
    indices.push_back(verts.size() - 2);
    indices.push_back(verts.size() - 1);
}
