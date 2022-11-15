#include "../chunk/Chunk.h"

class ChunkManager {
public:
    ChunkManager(int worldSeed);

    ~ChunkManager();

    void GenerateChunk(int x, int z);

    std::vector<Chunk *> chunks;

    void Update(int playerX, int playerZ, int renderDistance);

    void Draw();
};