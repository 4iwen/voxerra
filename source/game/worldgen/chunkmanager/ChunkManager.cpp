#include "ChunkManager.h"

#define CHUNK_SIZE 32
#define CHUNK_HEIGHT 512
#define BLOCK_SIZE 1.0f

ChunkManager::ChunkManager(int worldSeed) {
    Utils::noise->SetSeed(worldSeed);
    Utils::noise->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    Utils::noise->SetFrequency(0.01f);
    Utils::noise->SetFractalOctaves(4);
    Utils::noise->SetFractalLacunarity(2.0f);
    Utils::noise->SetFractalGain(0.5f);
}

ChunkManager::~ChunkManager() {
    for (auto &chunk : chunks) {
        delete chunk;
    }

    chunks.clear();
}

void ChunkManager::Update(int playerX, int playerZ, int renderDistance) {
    int playerChunkX = playerX / CHUNK_SIZE;
    int playerChunkZ = playerZ / CHUNK_SIZE;

    // delete chunks that out of the render distance
    for (int i = 0; i < chunks.size(); i++) {
        int chunkX = chunks[i]->chunkX;
        int chunkZ = chunks[i]->chunkZ;
        if (abs(chunkX - playerChunkX) > renderDistance || abs(chunkZ - playerChunkZ) > renderDistance) {
            delete chunks[i];
            chunks.erase(chunks.begin() + i);
        }
    }

    // generate chunks that are in the render distance
    for (int x = playerChunkX - renderDistance; x < playerChunkX + renderDistance; x++) {
        for (int z = playerChunkZ - renderDistance; z < playerChunkZ + renderDistance; z++) {
            bool chunkExists = false;
            for (int i = 0; i < chunks.size(); i++) {
                if (chunks[i]->chunkX == x && chunks[i]->chunkZ == z) {
                    chunkExists = true;
                    break;
                }
            }
            if (!chunkExists) {
                GenerateChunk(x, z);
            }
        }
    }
}

void ChunkManager::Draw() {
    for (int i = 0; i < chunks.size(); i++) {
        chunks[i]->Draw();
    }
}

void ChunkManager::GenerateChunk(int x, int z) {
    Chunk* chunk = new Chunk(x, z);
    chunk->Generate();
    chunk->GenerateVerticesAndIndices();
    chunks.push_back(chunk);
}