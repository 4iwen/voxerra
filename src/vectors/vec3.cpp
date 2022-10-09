//
// Created by Liquid on 10/9/2022.
//

#include <valarray>
#include "vec3.h"

vec3::vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
void vec3::zero()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

void vec3::one()
{
    this->x = 1;
    this->y = 1;
    this->z = 1;
}
void vec3::normalize() {
    float length = sqrt((x * x) + (y * y) + (z * z));
    x /= length;
    y /= length;
    z /= length;
}

float vec3::distance(vec3 a, vec3 b) {
    float x = a.x - b.x;
    float y = a.y - b.y;
    float z = a.z - b.z;
    float distance = sqrt((x * x) + (y * y) + (z * z));
    return distance;
}
