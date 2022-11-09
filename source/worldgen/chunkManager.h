#include "FastNoiseLite.h"
#include "chunk.h"

class chunkManager {
private:
    int indicesSize;
    int vertsSize;
    int width = 16;
    int height = 128;
    int length = 16;
    glm::vec2 playerPos = glm::vec2(0,0);
    FastNoiseLite noise;
    std::vector<chunk> chunks;

    std::vector<GLuint> *indices;
    std::vector<GLfloat> *vertices;

    int renderDistance = 1;

    void unloadChunk(chunk c);
    void addChunk(chunk c);

    void generateVerts();
    void generateIndices();


    bool RENDER_DISTANCE_CHECK(glm::vec2 pos);
public:
    void reloadChunks();
    int getRenderDistance();

    std::vector<chunk> getChunks();

    void updateChunks();

    void setRenderDistance(int distance);

    void generateVertArray();
    void generateIndiArray();
    void generateChunks(int x, int y);

    GLfloat * verticesARR;
    GLuint * indicesARR;

    GLfloat *getVertices();
    GLuint *getIndices();

    int getVertSize();
    int getIndiceSize();

    std::vector<GLuint> getIndicesVec();
    std::vector<GLfloat> getVerticesVec();
};
