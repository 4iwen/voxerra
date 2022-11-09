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

    std::cout << "Filling with air" << std::endl;
    fillBlocksWithAir();
    std::cout << "Generating Noise" << std::endl;
    generateNoise();
    std::cout << "Generating Verts" << std::endl;
    generateVerts();
    std::cout << "Generated vers" << std::endl;
}
void chunk::fillBlocksWithAir()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            for (int z = 0; z < length; z++)
            {
                blockData[x][y][z].type = blockType::AIR;
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
        for (int z = 0; z < length; ++z) {
            int y = generateHeight(x,z);
            blockData[x][y][z].type = blockType::GRASS;
            for (int i = y - 1; i > 0; i--)
            {
                if(i > y -5)
                {
                    blockData[x][i][z].type = blockType::DIRT;
                }
                else
                {
                    blockData[x][i][z].type = blockType::STONE;
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
                if (blockData[x][y][z].type != blockType::AIR) {
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

void chunk::ADD_LEFT_SIDE(int x, int y, int z)
{
    float r = blockData[x][y][z].red() / 255.0f;
    float g = blockData[x][y][z].green() / 255.0f;
    float b = blockData[x][y][z].blue() / 255.0f;

    verts.push_back(vert(vert::LEFT_TOP_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::LEFT_TOP_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::LEFT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::LEFT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    ADD_INDI_SIDE();
}
void chunk::ADD_RIGHT_SIDE(int x, int y, int z)
{
    float r = blockData[x][y][z].red() / 255.0f;
    float g = blockData[x][y][z].green() / 255.0f;
    float b = blockData[x][y][z].blue() / 255.0f;

    verts.push_back(vert(vert::RIGHT_TOP_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_TOP_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    ADD_INDI_SIDE();
}
void chunk::ADD_TOP_SIDE(int x, int y, int z)
{
    float r = blockData[x][y][z].red() / 255.0f;
    float g = blockData[x][y][z].green() / 255.0f;
    float b = blockData[x][y][z].blue() / 255.0f;

    verts.push_back(vert(vert::LEFT_TOP_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::LEFT_TOP_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_TOP_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_TOP_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    ADD_INDI_SIDE();
}
void chunk::ADD_BOTTOM_SIDE(int x, int y, int z)
{
    float r = blockData[x][y][z].red() / 255.0f;
    float g = blockData[x][y][z].green() / 255.0f;
    float b = blockData[x][y][z].blue() / 255.0f;

    verts.push_back(vert(vert::LEFT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::LEFT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    ADD_INDI_SIDE();
}
void chunk::ADD_FRONT_SIDE(int x, int y, int z)
{
    float r = blockData[x][y][z].red() / 255.0f;
    float g = blockData[x][y][z].green() / 255.0f;
    float b = blockData[x][y][z].blue() / 255.0f;

    verts.push_back(vert(vert::LEFT_TOP_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::LEFT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_TOP_FRONT_CORNER + glm::vec3(x,y,z),r,g,b));
    ADD_INDI_SIDE();
}
void chunk::ADD_BACK_SIDE(int x, int y, int z)
{
    float r = blockData[x][y][z].red() / 255.0f;
    float g = blockData[x][y][z].green() / 255.0f;
    float b = blockData[x][y][z].blue() / 255.0f;
    
    verts.push_back(vert(vert::LEFT_TOP_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::LEFT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_BOTTOM_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    verts.push_back(vert(vert::RIGHT_TOP_BACK_CORNER + glm::vec3(x,y,z),r,g,b));
    ADD_INDI_SIDE();
}

bool chunk::checkForBlock(int x, int y, int z)
{
    return blockData[x][y][z].type == blockType::AIR;
}

void chunk::GENERATE_GL_VERTS()
{
    GLverts.clear();
    for (int i = 0; i < verts.size(); i++) {
        GLverts.push_back(verts[i].position.x);
        GLverts.push_back(verts[i].position.y);
        GLverts.push_back(verts[i].position.z);
        GLverts.push_back(verts[i].position.r);
        GLverts.push_back(verts[i].position.g);
        GLverts.push_back(verts[i].position.b);
    }
}

std::vector<GLfloat>* chunk::getVerts()
{
    GENERATE_GL_VERTS();
    return &GLverts;
}

GLuint *chunk::getIncide(int i)
{
    return &indices.at( i);
}

GLfloat *chunk::getVert(int i)
{
    return &GLverts.at( i);
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
