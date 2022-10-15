//
// Created by Liquid on 8/29/2022.
//

#include "vert.h"

vert::vert(glm::vec3 pos, float red, float green, float blue) {
    this->position = pos;
    this->red = red;
    this->green = green;
    this->blue = blue;
}
vert vert::zero{
    vert(glm::vec3(0,0,0),0,0,0)
};

glm::vec3 vert::LEFT = glm::vec3(-1,0,0);
glm::vec3 vert::RIGHT = glm::vec3(1,0,0);
glm::vec3 vert::UP = glm::vec3(0,1,0);
glm::vec3 vert::DOWN = glm::vec3(0,-1,0);
glm::vec3 vert::FRONT = glm::vec3(0,0,1);
glm::vec3 vert::BACK = glm::vec3(0,0,-1);

glm::vec3 vert::RIGHT_TOP_FRONT_CORNER = glm::vec3(1,1,1);
glm::vec3 vert::RIGHT_TOP_BACK_CORNER = glm::vec3(1,1,0);
glm::vec3 vert::RIGHT_BOTTOM_FRONT_CORNER = glm::vec3(1,0,1);
glm::vec3 vert::RIGHT_BOTTOM_BACK_CORNER = glm::vec3(1,0,0);
glm::vec3 vert::LEFT_TOP_FRONT_CORNER = glm::vec3(0,1,1);
glm::vec3 vert::LEFT_TOP_BACK_CORNER = glm::vec3(0,1,0);
glm::vec3 vert::LEFT_BOTTOM_FRONT_CORNER = glm::vec3(0,0,1);
glm::vec3 vert::LEFT_BOTTOM_BACK_CORNER = glm::vec3(0,0,0);

void vert::changeColor(int r, int g,int b) {
    this->red = r;
    this->green = g;
    this->blue = b;
}
