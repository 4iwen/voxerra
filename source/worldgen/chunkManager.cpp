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

    for (int i = 0; i < getIndices().size(); ++i) {
        indicesARR[i] = getIndices()[i];
    }
    for (int i = 0; i < getVerts().size(); ++i) {
        verticesARR[i] = getVerts()[i];
    }
}

void chunkManager::updateChunks()
{
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
