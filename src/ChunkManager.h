//
// Created by Liquid on 9/24/2022.
//
#include "iostream"
#include "FastNoiseLite.h"
#include "vector"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "vert.h"
#include "Chunk.h"


#ifndef VOXERRA_CHUNKMANAGER_H
#define VOXERRA_CHUNKMANAGER_H


class ChunkManager {
private:
    int chunkCount;
    int playerPos;
    GLfloat allVerticies;
    GLuint allIndices;
    std::vector<Chunk> chunks;
    std::vector<GLfloat> verticies;
    std::vector<GLuint> indices;
public:
    int GetChunkCount();
    void LoadChunk(Chunk ic);
    void UnloadChunk(Chunk ic);
    GLfloat ReturnVerticies();
    GLuint ReturnIndices();
};


#endif //VOXERRA_CHUNKMANAGER_H
