#include "vector"
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

    void SetBlock(int x, int y, int z, BlockType type);

    void GenerateVerticesAndIndices();

    void GetVertices(std::vector<float> &vertices);

    void GetIndices(std::vector<unsigned int> &indices);



private:
    int _x;
    int _z;
    BlockType _chunkData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};