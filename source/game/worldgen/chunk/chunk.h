#include "vector"
#include "FastNoiseLite/FastNoiseLite.h"
#include "../../block/blocktype.h"
#include "../../../core/utils/utils.h"
#include "../mesh/vertex.h"
#include "../../../core/vertexarray/vertexarray.h"
#include "../../../core/vertexbuffer/vertexbuffer.h"
#include "../../../core/elementbuffer/elementbuffer.h"
#include "../mesh/mesh.h"

class Chunk {
public:
    Chunk(int x, int z);

    void generate();

    void generateVerticesAndIndices();

    void draw();

    int chunkX, chunkZ;

private:
    void addRightSide(int x, int y, int z);

    void addLeftSide(int x, int y, int z);

    void addTopSide(int x, int y, int z);

    void addBottomSide(int x, int y, int z);

    void addFrontSide(int x, int y, int z);

    void addBackSide(int x, int y, int z);

    Mesh mesh;
};