//
// Created by Liquid on 10/15/2022.
//

#ifndef VOXERRA_CHUNK_H
#define VOXERRA_CHUNK_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <vector>

#include "FastNoiseLite.h"
#include "../utils/vert.h"
#include "block.h"

class chunk {
public :
    chunk(int width, int height, int length,int posX,int posY,FastNoiseLite noise);

    std::vector<GLfloat>* getVerts();
    std::vector<GLint>* getIndices();

    int getIndiceSize();
    int getVertSize();

private :
    int width;
    int height;
    int length;
    int posX;
    int posY;
    FastNoiseLite noise;

    block blockData[32][512][32];

    std::vector<vert> verts;
    std::vector<GLfloat> GLverts;
    std::vector<GLint> indices;

    void generateVerts();
    void generateNoise();

    void fillBlocksWithAir();

    bool checkForBlock(int x, int y, int z);

    void ADD_LEFT_SIDE(int x, int y, int z);
    void ADD_RIGHT_SIDE(int x, int y, int z);
    void ADD_TOP_SIDE(int x, int y, int z);
    void ADD_BOTTOM_SIDE(int x, int y, int z);
    void ADD_FRONT_SIDE(int x, int y, int z);
    void ADD_BACK_SIDE(int x, int y, int z);

    void ADD_INDI_SIDE();

    int generateHeight(int x, int z);

    void GENERATE_GL_VERTS();
};


#endif //VOXERRA_CHUNK_H
