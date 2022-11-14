#include "FastNoiseLite.h"
#include "chunk.h"
#include "../core/VertexBuffer.h"
#include "../core/ElementBuffer.h"
#include <iostream>

class chunkManager {
private:
    int indicesSize = 0;
    int width = 16;
    int height = 128;
    int length = 16;
    glm::vec2 playerPos = glm::vec2(0,0);
    FastNoiseLite noise;
    std::vector<chunk> chunks;

    int renderDistance = 0;

    void unloadChunk(chunk c);
    void addChunk(chunk c);

    bool RENDER_DISTANCE_CHECK(glm::vec2 pos);

    void SET_DATA(chunk c,VertexBuffer *vbo, ElementBuffer *ebo);
public:
    void reloadChunks();
    int getRenderDistance();

    std::vector<chunk> getChunks();

    void updateChunks();

    void setRenderDistance(int distance);

    void generateChunks(int x, int y);

    int getIndiceSize();

    std::vector<GLuint> getIndicesVec();
    std::vector<GLfloat> getVerticesVec();

    void renderChunks(VertexBuffer *vbo, ElementBuffer *ebo);
    void generateData(VertexBuffer *vbo, ElementBuffer *ebo);
};
