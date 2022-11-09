#include <iostream>
#include "chunkManager.h"

void chunkManager::addChunk(chunk c)
{
    std::cout << "Adding chunk" << c.getPos().x  << "|" << c.getPos().y << std::endl;
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

void  chunkManager::generateVertArray(){
    verticesARR = new GLfloat[vertsSize];

    for (int i = 0; i < vertsSize; i++) {
        verticesARR[i] = vertices->at(i);
    }
}

void chunkManager::generateIndiArray(){
    indicesARR = new GLuint[indicesSize];
    std::cout << sizeof(indicesARR) << std::endl;
    for (int i = 0; i < indicesSize; i++) {
        indicesARR[i] = indices->at(i);
    }
}

GLfloat * chunkManager::getVertices()
{
    return verticesARR;
}

GLuint * chunkManager::getIndices()
{
    return indicesARR;
}

void chunkManager::generateChunks(int x, int y)
{
    for(int i = playerPos.x - x; i < playerPos.x + x; i++)
    {
        for(int j = playerPos.y - y; j < playerPos.y + y; j++)
        {
            addChunk(chunk(width,height,length,i,j,noise));
        }
    }
    generateVerts();
    generateIndices();
}

void chunkManager::updateChunks()
{
    std::cout << "Updating chunks" << std::endl;
    for(int i = playerPos.x - renderDistance; i <= playerPos.x; i++)
    {
        for(int j = playerPos.y - renderDistance; j <= playerPos.y; j++)
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
    generateIndices();
    generateVerts();
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

void chunkManager::generateIndices() {
    indices = new std::vector<GLuint>();
    indicesSize = 0;

    for (auto & chunk : chunks) {
        indices->insert(indices->end(),chunk.getIndices()->begin(),chunk.getIndices()->end());
        indicesSize += chunk.getIndiceSize();
    }
    generateIndiArray();
}

void chunkManager::generateVerts() {
    vertices = new std::vector<GLfloat>();
    vertsSize = 0;

    for (auto & chunk : chunks) {
        vertices->insert(vertices->end(),chunk.getVerts()->begin(),chunk.getVerts()->end());
        vertsSize += chunk.getVertSize();
    }
    generateVertArray();
}

void chunkManager::setRenderDistance(int distance)
{
    renderDistance = distance;
}

int chunkManager::getRenderDistance()
{
    return renderDistance;
}

int chunkManager::getVertSize()
{
    return vertsSize;
}

int chunkManager::getIndiceSize()
{
    return indicesSize;
}

std::vector<GLuint> chunkManager::getIndicesVec()
{
    return *indices;
}
std::vector<GLfloat> chunkManager::getVerticesVec()
{
    return *vertices;
}