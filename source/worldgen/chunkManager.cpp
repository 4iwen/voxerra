#include <iostream>
#include "chunkManager.h"

void chunkManager::addChunk(chunk c)
{
    std::cout << "Adding chunk" << c.getPos().x  << c.getPos().y << std::endl;
    chunks.push_back(c);
}

void chunkManager::reloadChunks()
{
    for (int i = 0; i < chunks.size(); i++)
    {
        unloadChunk(chunks[i]);
    }
    updateChunks();
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

GLfloat * chunkManager::generateVertArray(){
    verticesARR = new GLfloat[getVerts().size()];

    for (int i = 0; i < getVerts().size(); ++i) {
        verticesARR[i] = getVerts()[i];
    }
    return verticesARR;
}

GLuint * chunkManager::generateIndiArray(){
    indicesARR = new GLuint[getVerts().size()];

    for (int i = 0; i < getVerts().size(); ++i) {
        verticesARR[i] = getVerts()[i];
    }
    return indicesARR;
}

void chunkManager::updateChunks()
{
    std::cout << "Updating chunks" << std::endl;
    for(int i = playerPos.x - renderDistance; i < playerPos.x + renderDistance; i++)
    {
        for(int j = playerPos.y - renderDistance; j < playerPos.y + renderDistance; j++)
        {
            bool found = false;
            for (auto & chunk : chunks) {
                if(!RENDER_DISTANCE_CHECK(chunk.getPos()))
                {
                    unloadChunk(chunk);
                    found = true;
                    break;
                }
                if(chunk.getPos() == glm::vec2(i,j))
                {
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                chunk c = chunk(16,256,16,i,j,noise);
                addChunk(c);
            }
        }
    }
}

bool chunkManager::RENDER_DISTANCE_CHECK(glm::vec2 pos)
{
    if(pos.x < playerPos.x - renderDistance
    || pos.x > playerPos.x + renderDistance
    || pos.y < playerPos.y - renderDistance
    || pos.y > playerPos.y+ renderDistance)
    {
        return false;
    }
    return true;
}

std::vector<GLuint> chunkManager::getIndices() {
    for (auto & chunk : chunks) {
        for (int i = 0; i < chunk.getIndiceSize(); ++i) {
            indices->push_back(*chunk.getIncide(i));
        }
    }
    return *indices;
}

std::vector<GLfloat> chunkManager::getVerts() {
    for (auto & chunk : chunks) {
        for (int i = 0; i < chunk.getVertSize(); ++i) {
            vertices->push_back(*chunk.getVert(i));
        }
    }
    return *vertices;
}

void chunkManager::setRenderDistance(int distance)
{
    renderDistance = distance;
}

int chunkManager::getRenderDistance()
{
    return renderDistance;
}
