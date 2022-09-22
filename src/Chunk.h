#include "iostream"
#include "FastNoiseLite.h"
#include "vector"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "vert.h"

using namespace std;

#ifndef VOXERRA_CHUNK_H

class Chunk{
public:
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

    enum blocks {air, dirt, grass,stone,bedrock};
    blocks blockData[16][16][32];

    bool CheckAround(int x,int y,int z);

    void AddVert(vert i);
    void AddTop(int blockX,int blockY,int blockZ);
    void AddBottom(int blockX,int blockY,int blockZ);
    void AddLeft(int blockX,int blockY,int blockZ);
    void AddRight(int blockX,int blockY,int blockZ);
    void AddBack(int blockX,int blockY,int blockZ);
    void AddForth(int blockX,int blockY,int blockZ);

    void GenerateIndicies();

    int posX;
    int posY;

    int v = 0;
    int i = 0;

    int width;
    int length;
    int height;
};

#define VOXERRA_CHUNK_H

#endif //VOXERRA_CHUNK_H
