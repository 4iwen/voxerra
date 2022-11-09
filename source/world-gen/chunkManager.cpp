//
// Created by Liquid on 10/15/2022.
//

#include "chunkManager.h"

void chunkManager::addChunk(chunk c)
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
    for (int x = 0; x < chunks.size(); x++) {
        indices.push_back(chunks[x].getIndices());
        vertices.push_back(chunks[x].getVerts());
    }
}