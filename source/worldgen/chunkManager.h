#include "FastNoiseLite.h"
#include "chunk.h"

class chunkManager {
    private:
        int width;
        int height;
        int length;
        FastNoiseLite noise;
        std::vector<chunk> chunks;

        std::vector<GLuint> *indices;
        std::vector<GLfloat> *vertices;

        void loadChunks();

    public:
        void loadChunk();
        void unloadChunk();
        void removeChunk(chunk c);
        void addChunk(const chunk& c);
        std::vector<chunk> getChunks();
        std::vector<GLfloat> getVerts();
        std::vector<GLint> getIndices();
        void generateChunk();
};
