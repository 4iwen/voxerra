//
// Created by Liquid on 10/15/2022.
//

#include "chunkManager.h"

void chunkManager::addChunk(const chunk& c)
{
    chunks.push_back(c);
}
void chunkManager::removeChunk(chunk c)
{
    for (int x = 0; x < chunks.size(); x++)
    {
        if(chunks[x].getIndices() == c.getIndices() && chunks[x].getVerts() == c.getVerts())
        {
            chunks.erase(chunks.begin() + x);
            return;
        }
    }
}

void chunkManager::loadChunks()
{
    for (int x = 0; x < chunks.size(); x++)
    {
        loadChunk();
    }
}
void chunkManager::loadChunk() {
    for (auto & chunk : chunks) {
        std::vector<GLfloat> *CHUNK_VERTS = chunk.getVerts();
        std::vector<GLint> *CHUNK_INDICES = chunk.getIndices();
        std::push_heap(CHUNK_VERTS->begin(), CHUNK_VERTS->end());
        std::push_heap(CHUNK_INDICES->begin(), CHUNK_INDICES->end());
    }
}