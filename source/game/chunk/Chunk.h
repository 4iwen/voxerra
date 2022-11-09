#include "vector"
#include "FastNoiseLite/FastNoiseLite.h"
#include "../Block/BlockType.h"
#include "../../core/utils/Utils.h"
#include "../Vertex.h"

class Chunk {
public:
    Chunk(int x, int z);

    void Render();

    void Generate();

    void GenerateVerticesAndIndices();

    void GetVertices(std::vector<float> &vertices);

    void GetIndices(std::vector<unsigned int> &indices);

    int chunkX, chunkZ;

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int indicesIndex = 0;

    void AddRightSide(int x, int y, int z);

    void AddLeftSide(int x, int y, int z);

    void AddTopSide(int x, int y, int z);

    void AddBottomSide(int x, int y, int z);

    void AddFrontSide(int x, int y, int z);

    void AddBackSide(int x, int y, int z);

    void AddVertices(Vertex vertex, Vertex vertex1, Vertex vertex2, Vertex vertex3);

    void AddIndices();

    BlockColor GetBlockColor(BlockType type);
};

