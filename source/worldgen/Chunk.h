#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <vector>

#include "FastNoiseLite.h"
#include "../utils/enums.h"
#include "Mesh.h"

using namespace glm;

class Chunk {
public :
#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

glm::vec3 vertex_positions[6][4] = {
        {vec3(1,0,0), vec3(1,1,0), vec3(1,0,1), vec3(1,1,1)},
        {vec3(0,0,0), vec3(0,1,0), vec3(0,0,1), vec3(0,1,1)},
        {vec3(0,1,0), vec3(1,1,0), vec3(0,1,1), vec3(1,1,1)},
        {vec3(0,0,0), vec3(1,0,0), vec3(0,0,1), vec3(1,0,1)},
        {vec3(0,0,1), vec3(1,0,1), vec3(0,1,1), vec3(1,1,1)},
        {vec3(0,0,0), vec3(1,0,0), vec3(0,1,0), vec3(1,1,0)}
};

    Chunk(int posX, int posZ, FastNoiseLite noise);
    Mesh mesh;

    glm::vec2 getPos();

    void GenerateNoise();

    bool isChunkInRenderDistance(float d, float d1, int i);
    void DrawChunk(Shader shader);
    void GenerateMesh();

private :
    int posX;
    int posZ;
    FastNoiseLite noise;

    blockType blockData[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

    std::vector<Vertex> vertices;
    std::vector<GLfloat> floatVertices;
    std::vector<GLuint> indices;

    void FillBlocksWithAir();

    bool CheckForBlock(int x, int y, int z);
    int GenerateHeight(int x, int z);

    glm::vec3 ColorPicker(blockType type);

    void AddVertex(int face, int x, int y, int z);
};

