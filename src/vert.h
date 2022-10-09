//
// Created by Liquid on 8/29/2022.
//
#ifndef VOXERRA_INDI_H
#define VOXERRA_INDI_H


#include "vectors/vec3.h"
#include "glm/glm.hpp"

class vert {
public :
    vert(glm::vec3 pos, float red, float green, float blue);

    glm::vec3 position;
    int red;
    int green;
    int blue;
};


#endif //VOXERRA_INDI_H
