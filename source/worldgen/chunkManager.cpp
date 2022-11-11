#include <iostream>
#include "chunkManager.h"

void chunkManager::addChunk(chunk c)
{
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

void chunkManager::SET_RENDERER(VertexBuffer *vbo, ElementBuffer *ebo)
{
    this->vbo = vbo;
    this->ebo = ebo;
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
    renderChunks();
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
                chunk c = chunk(16,256,16,2,3,noise);
                addChunk(c);
            }
        }
    }
}

void chunkManager::renderChunks()
{
    for (auto & chunk : chunks) {
        SET_DATA(chunk);
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

void chunkManager::setRenderDistance(int distance)
{
    renderDistance = distance;
}

int chunkManager::getRenderDistance()
{
    return renderDistance;
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

void chunkManager::SET_DATA(chunk c)
{
    GLuint indicesARR[c.getIndiceSize()];
    GLfloat verticesARR[c.getVertSize()];
    indicesSize += c.getIndiceSize();

    for (int i = 0; i < c.getIndiceSize(); i++) {
        indicesARR[i] = c.getIndices()->at(i);
    }

    for (int v = 0; v < c.getVertSize(); v++) {
        verticesARR[v] = c.getVerts()->at(v);

    }
    vbo->Bind();
    vbo->SetData(verticesARR, sizeof(verticesARR));
    ebo->Bind();
    ebo->SetData(indicesARR, sizeof(indicesARR));

    std::cout << "Chunk: " << c.getPos().x << " " << c.getPos().y << std::endl;
    std::cout << "Indices: " << c.getIndiceSize() << std::endl;
    std::cout << "Vertices: " << c.getVertSize() << std::endl;

}