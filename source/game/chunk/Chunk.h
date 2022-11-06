#include "vector"
#include "FastNoiseLite/FastNoiseLite.h"
#include "../Block/Block.h"
#include "../../core/utils/Utils.h"
#include "../Vertex.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

class Chunk {
public:
    Chunk(int x, int z);

    void Render();

    void Generate();

    Block GetBlock(int x, int y, int z);

    void SetBlock(int x, int y, int z, Block block);

    void GenerateVerticesAndIndices();

    void GetVertices(std::vector<float> &vertices);

    void GetIndices(std::vector<unsigned int> &indices);

private:
    int _x, _z;
    Block _chunkData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]{};

    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
    int _indicesIndex = 0;

    void AddRightSide(int x, int y, int z);

    void AddLeftSide(int x, int y, int z);

    void AddTopSide(int x, int y, int z);

    void AddBottomSide(int x, int y, int z);

    void AddFrontSide(int x, int y, int z);

    void AddBackSide(int x, int y, int z);

    glm::vec3 GetBlockColor(BlockType type);

    void AddVertices(Vertex vertex, Vertex vertex1, Vertex vertex2, Vertex vertex3);

    void AddIndices();
};

