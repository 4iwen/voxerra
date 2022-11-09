#pragma once

#include "glm/vec3.hpp"
#include "block/BlockType.h"

class Vertex {
public:
    Vertex(glm::vec3 position, BlockColor color);

    glm::vec3 LEFT = glm::vec3(-1,0,0);
    glm::vec3 RIGHT = glm::vec3(1,0,0);
    glm::vec3 UP = glm::vec3(0,1,0);
    glm::vec3 DOWN = glm::vec3(0,-1,0);
    glm::vec3 FRONT = glm::vec3(0,0,1);
    glm::vec3 BACK = glm::vec3(0,0,-1);

    glm::vec3 RIGHT_TOP_FRONT_CORNER = glm::vec3(1,1,1);
    glm::vec3 RIGHT_TOP_BACK_CORNER = glm::vec3(1,1,0);
    glm::vec3 RIGHT_BOTTOM_FRONT_CORNER = glm::vec3(1,0,1);
    glm::vec3 RIGHT_BOTTOM_BACK_CORNER = glm::vec3(1,0,0);
    glm::vec3 LEFT_TOP_FRONT_CORNER = glm::vec3(0,1,1);
    glm::vec3 LEFT_TOP_BACK_CORNER = glm::vec3(0,1,0);
    glm::vec3 LEFT_BOTTOM_FRONT_CORNER = glm::vec3(0,0,1);
    glm::vec3 LEFT_BOTTOM_BACK_CORNER = glm::vec3(0,0,0);

    glm::vec3 position;
    BlockColor color;
};