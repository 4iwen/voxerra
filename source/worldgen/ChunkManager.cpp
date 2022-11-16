#include "ChunkManager.h"

using namespace std;

void ChunkManager::addChunk(int pos_x, int pos_z) {
    Chunk* c = new Chunk(pos_x, pos_z,noise);
    c->GenerateNoise();
    c->GenerateMesh();
}

void ChunkManager::drawChunks(Shader& shader) {
    for(auto& chunk : chunks) {
        chunk->DrawChunk(shader);
    }
}

void ChunkManager::updateChunks(float player_x, float player_z) {
    int limit_x = (int)player_x / CHUNK_SIZE;
    int limit_z = (int)player_z / CHUNK_SIZE;

    for(auto chunk : chunks) {
        if(chunk->isChunkInRenderDistance(player_x, player_z, RENDER_DISTANCE)) {
            remove(chunks.begin(), chunks.end(), chunk);
            }
        }
    int loaded_chunks = 0;
    for (int chunk_x = limit_x - RENDER_DISTANCE; chunk_x <= limit_x + RENDER_DISTANCE; chunk_x++) {
        for (int chunk_z = limit_z - RENDER_DISTANCE; chunk_z <= limit_z + RENDER_DISTANCE; chunk_z++) {
            Chunk c = Chunk(chunk_x, chunk_z, noise);
            if (find(chunks.begin(), chunks.end(), &c) != chunks.end() ) {
                addChunk(chunk_x, chunk_z);
                loaded_chunks++;
            }
            if (loaded_chunks >= frame_load_limit) break;
        }
    }
}

void ChunkManager::reloadChunks(float player_x, float player_z) {
    int limit_x = (int)player_x / CHUNK_SIZE;
    int limit_z = (int)player_z / CHUNK_SIZE;

    chunks.clear();

    for (int pos_x = limit_x - RENDER_DISTANCE; pos_x <= limit_x + RENDER_DISTANCE; pos_x++) {
        for (int pos_z = limit_z - RENDER_DISTANCE; pos_z <= limit_z + RENDER_DISTANCE; pos_z++) {
            addChunk(pos_x, pos_z);
        }
    }
}