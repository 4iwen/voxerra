#include "vector"
#include "FastNoiseLite/FastNoiseLite.h"
#include "../../block/blocktype.h"
#include "../../../core/utils/utils.h"
#include "../mesh/Vertex.h"
#include "../../../core/vertexarray/vertexarray.h"
#include "../../../core/vertexbuffer/vertexbuffer.h"
#include "../../../core/elementbuffer/elementbuffer.h"
#include "../mesh/Mesh.h"

class Chunk {
public:
    Chunk(int x, int z);

    void generate();

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