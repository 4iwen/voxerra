#include <map>
#include "iostream"
#include "FastNoiseLite.h"
#include "vector"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "../utils/vert.h"
#include "block.h"


using namespace std;

#ifndef VOXERRA_CHUNK_H

class Chunk{
public:
    Chunk() {};

    void GenerateChunk(FastNoiseLite noise, int posX,int posY, int length, int width, int height);
    vector<GLuint>* ReturnIndecies();
    vector<GLfloat>* ReturnVerticies();
    int ReturnIndeciesSize();
    int ReturnVerticiesSize();

private:
    vector<GLfloat> GLvertices;
    vector<GLuint> GLindices;
    vector<vert> verts;

    void GenerateVertices();
    void GenerateGLData();
    void GenerateNoise(FastNoiseLite noise);
    void FillEmpty();

    block blockData[16][16][32];

    bool CheckAround(glm::vec3);

    void AddVert(vert i);
    void AddTop(int blockX,int blockY,int blockZ,int r ,int g ,int b);
    void AddBottom(int blockX,int blockY,int blockZ,int r ,int g ,int b);
    void AddLeft(int blockX,int blockY,int blockZ,int r ,int g ,int b);
    void AddRight(int blockX,int blockY,int blockZ,int r ,int g ,int b);
    void AddBack(int blockX,int blockY,int blockZ,int r ,int g ,int b);
    void AddForth(int blockX,int blockY,int blockZ,int r ,int g ,int b);

    int posX;
    int posY;

    int width;
    int length;
    int height;

    void PushBackIndicies();
};

#define VOXERRA_CHUNK_H

#endif //VOXERRA_CHUNK_H
