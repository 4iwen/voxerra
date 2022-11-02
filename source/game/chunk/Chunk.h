#include "FastNoiseLite/FastNoiseLite.h"
#include "../Block/Block.h"
#include "../../core/utils/Utils.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

class Chunk {
public:
    Chunk(int x, int z);

    ~Chunk();

    void Render();

    void Generate();

    Block GetBlock(int x, int y, int z);

    void SetBlock(int x, int y, int z, Block block);

private:
    int _x;
    int _z;
    Block _chunkData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
};