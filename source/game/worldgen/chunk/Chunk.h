#include "vector"
#include "FastNoiseLite/FastNoiseLite.h"
#include "../../block/BlockType.h"
#include "../../../core/utils/Utils.h"
#include "../mesh/Vertex.h"
#include "../../../core/VertexArray.h"
#include "../../../core/VertexBuffer.h"
#include "../../../core/ElementBuffer.h"
#include "../mesh/Mesh.h"

class Chunk {
public:
    Chunk(int x, int z);

    void Generate();

    void GenerateVerticesAndIndices();

    void Draw();

    int chunkX, chunkZ;

    Mesh mesh;

private:
    void AddRightSide(int x, int y, int z);

    void AddLeftSide(int x, int y, int z);

    void AddTopSide(int x, int y, int z);

    void AddBottomSide(int x, int y, int z);

    void AddFrontSide(int x, int y, int z);

    void AddBackSide(int x, int y, int z);
};