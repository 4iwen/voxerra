#include "ChunkManager.h"

void ChunkManager::addChunk()
{
    Chunk c = Chunk(width, height, length, c.getPos().x, c.getPos().y, noise);
}

void ChunkManager::reloadChunks()
{
    for (int i = 0; i < chunks.size(); i++)
    {
        unloadChunk(chunks[i]);
    }
    updateChunks();
}

void ChunkManager::unloadChunk(Chunk c) {
    for (int x = 0; x < chunks.size(); x++)
    {
        if(chunks[x].getPos() == c.getPos())
        {
            chunks.erase(chunks.begin() + x);
            return;
        }
    }
}

void ChunkManager::generateChunks(int x, int y)
{
    for(int i = playerPos.x - x; i <= playerPos.y + x; i++)
    {
        for(int j = playerPos.y - y; j <= playerPos.y + y; j++)
        {
            addChunk(Chunk(width, height, length, i, j, noise));
        }
    }
}

void ChunkManager::updateChunks()
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
                Chunk c = Chunk(16, 256, 16, i, j, noise);
                addChunk(c);
            }
        }
    }
}

bool ChunkManager::RENDER_DISTANCE_CHECK(glm::vec2 pos)
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

void ChunkManager::setRenderDistance(int distance)
{
    renderDistance = distance;
}

int ChunkManager::getRenderDistance()
{
    return renderDistance;
}

int ChunkManager::getIndiceSize()
{
    return indicesSize;
}
