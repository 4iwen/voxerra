#include "Chunk.h"

class ChunkManager {
public:
    ChunkManager();

    ~ChunkManager();

    void GenerateChunk(int x, int z);

    void GenerateChunks(int x, int z);

    void GetChunks(std::vector<Chunk*>& chunks);

private:
    std::vector<Chunk*> _chunks;
};