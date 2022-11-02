#include "FastNoiseLite.h"
#include "chunk.h"

class chunkManager {
private:
    int width = 16;
    int height = 128;
    int length = 16;
    glm::vec2 playerPos = glm::vec2(0,0);
    FastNoiseLite noise;
    std::vector<chunk> chunks;

    std::vector<GLuint> *indices;
    std::vector<GLfloat> *vertices;

    GLuint *indicesARR;
    GLfloat *verticesARR;

    int renderDistance = 2;
    void reloadChunks();

    void unloadChunk(chunk c);
    void addChunk(chunk c);
    int getRenderDistance();



    bool RENDER_DISTANCE_CHECK(glm::vec2 pos);
public:

    std::vector<chunk> getChunks();

    std::vector<GLfloat> getVerts();
    std::vector<GLuint> getIndices();

    void updateChunks();

    void setRenderDistance(int distance);

    GLfloat * generateVertArray();
    GLuint * generateIndiArray();
};
