#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <vector>

#include "FastNoiseLite.h"
#include "../utils/vert.h"
#include "../utils/enums.h"
#include "Mesh.h"
#include "../core/Shader.h"

#define CHUNK_WIDTH 16
#define CHUNK_LENGTH 16
#define CHUNK_HEIGHT 256

class Chunk {
public :
    Chunk(int posX, int posY);
    std::vector<GLfloat>* getVerts();
    std::vector<GLuint>* getIndices();
    Mesh mesh;

    glm::vec2 getPos();

    void GenerateNoise(FastNoiseLite noise);

private :
    int posX;
    int posY;

    FastNoiseLite noise;

    blockType blockData[16][256][16];

    std::vector<Vertex> vertices;
    std::vector<GLfloat> floatVertices;
    std::vector<GLuint> indices;

    void GenerateMesh();

    void FillBlocksWithAir();

    bool CheckForBlock(int x, int y, int z);

    void ADD_LEFT_SIDE(int x, int y, int z);
    void ADD_RIGHT_SIDE(int x, int y, int z);
    void ADD_TOP_SIDE(int x, int y, int z);
    void ADD_BOTTOM_SIDE(int x, int y, int z);
    void ADD_FRONT_SIDE(int x, int y, int z);
    void ADD_BACK_SIDE(int x, int y, int z);

    void ADD_INDI_SIDE();

    int GenerateHeight(int x, int z);

    void GENERATE_GL_VERTS();
    glm::vec3 PICK_BLOCK_COLOR(blockType type);

    void DrawChunk(Shader shader);
};

