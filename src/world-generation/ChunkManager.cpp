//
// Created by Liquid on 9/24/2022.
//

#include "ChunkManager.h"

void ChunkManager::LoadChunk(Chunk c)
{
    chunks.push_back(c);
}

void ChunkManager::UnloadChunk(Chunk c)
{
    for (int x = 0; x < chunks.size(); x++)
    {
        if(chunks[x].ReturnIndecies() == c.ReturnIndecies() && chunks[x].ReturnVerticies() == c.ReturnVerticies())
        {
            chunks.erase(chunks.begin() + x);
            return;
        }
    }
}

int ChunkManager::GetChunkCount() {
    return chunks.size();
}

GLfloat ChunkManager::ReturnVerticies() {
    return verticies.size();
}

GLuint ChunkManager::ReturnIndices() {
    return indices.size();
}
