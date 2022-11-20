#include "FastNoiseLite.h"
#include "Chunk.h"
#include "../core/VertexBuffer.h"
#include "../core/ElementBuffer.h"
#include <iostream>
#include <unordered_map>

class ChunkManager {
private:

    const int RENDER_DISTANCE = 8;

public:
    int frame_load_limit = 4;
    FastNoiseLite noise;

    ChunkManager(FastNoiseLite noise)
    {
        this->noise = noise;
    }
    vector<Chunk*> chunks;
    void addChunk(int coordinate_x, int coordinate_z);
    void drawChunks(Shader& shader);
    void updateChunks(float position_x, float position_z);
    void reloadChunks(float position_x, float position_z);
};
