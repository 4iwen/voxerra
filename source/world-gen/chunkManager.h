//
// Created by Liquid on 10/15/2022.
//

#ifndef VOXERRA_CHUNKMANAGER_H
#define VOXERRA_CHUNKMANAGER_H


#include "FastNoiseLite.h"
#include "chunk.h"

class chunkManager {
    private:
        int width;
        int height;
        int length;
        FastNoiseLite noise;
        std::vector<chunk> chunks;

        std::vector<GLint> indices;
        std::vector<GLfloat> vertices;

        void loadChunks();

    public:
        void loadChunk();
        void unloadChunk();
        void removeChunk(chunk c);
        void addChunk(chunk c);
        std::vector<chunk> getChunks();
        std::vector<GLfloat> getVerts();
        std::vector<GLint> getIndices();
        void generateChunk();
};


#endif //VOXERRA_CHUNKMANAGER_H
