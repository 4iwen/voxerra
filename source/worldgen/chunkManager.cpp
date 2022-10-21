//
// Created by Liquid on 10/15/2022.
//

#include "chunkManager.h"

void chunkManager::addChunk(const chunk& c)
{
    chunks.push_back(c);
}
void chunkManager::unloadChunk(chunk c) {
    for (int x = 0; x < chunks.size(); x++)
    {
        if(chunks[x].getPos() == c.getPos())
        {
            chunks.erase(chunks.begin() + x);
            return;
        }
    }
}

void chunkManager::loadChunks()
{
    for (auto & chunk : chunks) {
        loadChunk(chunk);
    }
}
void chunkManager::loadChunk(chunk c) {
        std::push_heap(c.getVerts()->begin(), c.getVerts()->end());
        std::push_heap(c.getIndices()->begin(), c.getIndices()->end());
}

GLfloat* chunkManager::getArrayVerts(){
    return verticesARR;
}
GLuint* chunkManager::getArrayIndices(){
    return indicesARR;
}

void chunkManager::generateArrays(){
    indicesARR = new GLuint[getIndices().size()];
    verticesARR = new GLfloat[getVerts().size()];

    indicesARR = indices->data();
    verticesARR = vertices->data();
}

void chunkManager::generateChunk() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < length; z++) {
                chunk c = chunk( 16, 256, 16,x, y, noise);
                addChunk(c);
            }
        }
    }
    loadChunks();
    generateArrays();
}
