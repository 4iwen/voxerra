//
// Created by Liquid on 10/9/2022.
//

#include <valarray>
#include "vec2.h"

vec2::vec2(float x, float y) {
    this->x = x;
    this->y = y;
}
void vec2::zero()
{
    this->x = 0;
    this->y = 0;
}

void vec2::one()
{
    this->x = 1;
    this->y = 1;
}
void vec2::normalize() {
    float length = sqrt((x * x) + (y * y));
    x /= length;
    y /= length;
}

float vec2::distance(vec2 a, vec2 b) {
    float x = a.x - b.x;
    float y = a.y - b.y;
    float distance = sqrt((x * x) + (y * y));
    return distance;
}