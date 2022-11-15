#include "glm/glm.hpp"
#include <vector>
#pragma once

class vert {
public :
    static vert zero;
    static glm::vec3 LEFT;
    static glm::vec3 RIGHT;
    static glm::vec3 UP;
    static glm::vec3 DOWN;
    static glm::vec3 FRONT;
    static glm::vec3 BACK;

    static glm::vec3 RIGHT_TOP_FRONT_CORNER;
    static glm::vec3 RIGHT_TOP_BACK_CORNER;
    static glm::vec3 RIGHT_BOTTOM_FRONT_CORNER;
    static glm::vec3 RIGHT_BOTTOM_BACK_CORNER;
    static glm::vec3 LEFT_TOP_FRONT_CORNER;
    static glm::vec3 LEFT_TOP_BACK_CORNER;
    static glm::vec3 LEFT_BOTTOM_FRONT_CORNER;
    static glm::vec3 LEFT_BOTTOM_BACK_CORNER;
};

