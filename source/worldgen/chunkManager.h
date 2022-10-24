#include "FastNoiseLite.h"
#include "chunk.h"

class chunkManager {
private:
    int width;
    int height;
    int length;
    glm::vec2 playerPos = glm::vec2(0,0);
    FastNoiseLite noise;
    std::vector<chunk> chunks;

    std::vector<GLuint> *indices;
    std::vector<GLfloat> *vertices;

    GLuint *indicesARR;
    GLfloat *verticesARR;

    int renderDistance = 1;
    void loadChunks();

public:
    void loadChunk(chunk c);
    void unloadChunk(chunk c);
    void addChunk(const chunk& c);
    std::vector<chunk> getChunks();
    std::vector<GLfloat> getVerts();
    std::vector<GLuint> getIndices();
    GLfloat* getArrayVerts();
    GLuint* getArrayIndices();

    int getRenderDistance;
    int setRenderDistance;

    void generateArrays();

    bool RENDER_DISTANCE_CHECK(glm::vec2 pos);

    void updateChunks();
};
