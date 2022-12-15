#include "chunkmanager.h"

#define CHUNK_SIZE 32
#define CHUNK_HEIGHT 512
#define BLOCK_SIZE 1.0f

ChunkManager::ChunkManager(int worldSeed) {
    Utils::s_noise.SetSeed(worldSeed);
    Utils::s_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    Utils::s_noise.SetFrequency(0.01f);
    Utils::s_noise.SetFractalOctaves(4);
    Utils::s_noise.SetFractalLacunarity(2.0f);
    Utils::s_noise.SetFractalGain(0.5f);
}

ChunkManager::~ChunkManager() {
    for (auto &chunk: m_chunks) {
        delete chunk;
    }

    m_chunks.clear();
}

void ChunkManager::update(int playerX, int playerZ, int renderDistance) {
    int playerChunkX = playerX / CHUNK_SIZE;
    int playerChunkZ = playerZ / CHUNK_SIZE;

    // delete m_chunks that out of the render distance
    for (int i = 0; i < m_chunks.size(); i++) {
        int chunkX = m_chunks[i]->chunkX;
        int chunkZ = m_chunks[i]->chunkZ;
        if (abs(chunkX - playerChunkX) > renderDistance || abs(chunkZ - playerChunkZ) > renderDistance) {
            delete m_chunks[i];
            m_chunks.erase(m_chunks.begin() + i);
        }
    }

    // generate m_chunks that are in the render distance
    for (int x = playerChunkX - renderDistance; x < playerChunkX + renderDistance; x++) {
        for (int z = playerChunkZ - renderDistance; z < playerChunkZ + renderDistance; z++) {
            bool chunkExists = false;
            for (int i = 0; i < m_chunks.size(); i++) {
                if (m_chunks[i]->chunkX == x && m_chunks[i]->chunkZ == z) {
                    chunkExists = true;
                    break;
                }
            }
            if (!chunkExists) {
                generateChunk(x, z);
            }
        }
    }
}

void ChunkManager::draw() {
    for (int i = 0; i < m_chunks.size(); i++) {
        m_chunks[i]->draw();
    }
}

void ChunkManager::generateChunk(int x, int z) {
    Chunk *chunk = new Chunk(x, z);
    chunk->generate();
    chunk->generateVerticesAndIndices();
    m_chunks.push_back(chunk);
}