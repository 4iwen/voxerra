#include <iostream>
#include "ChunkManager.h"

ChunkManager::ChunkManager() {

}

ChunkManager::~ChunkManager() {
    for (int i = 0; i < _chunks.size(); i++) {
        delete _chunks[i];
    }
}

void ChunkManager::GenerateChunk(int x, int z) {
    Chunk *chunk = new Chunk(x, z);
    chunk->Generate();
    std::cout << "generated terrain" << std::endl;
    chunk->GenerateVerticesAndIndices();
    std::cout << "generated vertices and indices" << std::endl;
    _chunks.push_back(chunk);
    std::cout << "chunk at: " << x << " " << z << " generated" << std::endl;
}

void ChunkManager::GenerateChunks(int x, int z) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < z; j++) {
            GenerateChunk(i, j);
        }
    }
}

void ChunkManager::GetChunks(std::vector<Chunk *> &chunks) {
    chunks = _chunks;
}