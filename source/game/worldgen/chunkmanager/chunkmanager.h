#include "../chunk/chunk.h"

class ChunkManager {
public:
    ChunkManager(int worldSeed);

    ~ChunkManager();

    void update(int playerX, int playerZ, int renderDistance);

    void draw();

private:
    void generateChunk(int x, int z);

    std::vector<Chunk *> m_chunks = {};
};