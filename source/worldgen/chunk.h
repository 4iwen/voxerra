#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <vector>

#include "FastNoiseLite.h"
#include "../utils/vert.h"
#include "../utils/enums.h"

class chunk {
public :
    chunk(int width, int height, int length,int posX,int posY, FastNoiseLite noise);
    std::vector<GLfloat>* getVerts();
    std::vector<GLuint>* getIndices();

    int getIndiceSize();
    int getVertSize();

    glm::vec2 getPos();

private :
    int width;
    int height;
    int length;

    int posX;
    int posY;

    FastNoiseLite noise;

    blockType blockData[16][256][16];

    std::vector<vert> verts;
    std::vector<GLfloat> GLverts;
    std::vector<GLuint> indices;

    void generateVerts();
    void generateNoise();

    void fillBlocksWithAir();

    bool checkForBlock(int x, int y, int z);

    void ADD_LEFT_SIDE(int x, int y, int z);
    void ADD_RIGHT_SIDE(int x, int y, int z);
    void ADD_TOP_SIDE(int x, int y, int z);
    void ADD_BOTTOM_SIDE(int x, int y, int z);
    void ADD_FRONT_SIDE(int x, int y, int z);
    void ADD_BACK_SIDE(int x, int y, int z);

    void ADD_INDI_SIDE();

    int generateHeight(int x, int z);

    void GENERATE_GL_VERTS();
    glm::vec3 PICK_BLOCK_COLOR(blockType type);
};

