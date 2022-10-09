//
// Created by Liquid on 10/9/2022.
//

#ifndef VOXERRA_VEC3_H
#define VOXERRA_VEC3_H


class vec3 {
public:
    vec3(float x, float y, float z);
    float x;
    float y;
    float z;

    void zero();
    void one();
    void normalize();
    float distance(vec3 a, vec3 b);
};


#endif //VOXERRA_VEC3_H
