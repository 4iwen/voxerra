//
// Created by Liquid on 10/9/2022.
//

#ifndef VOXERRA_VEC2_H
#define VOXERRA_VEC2_H


class vec2 {
public:
    vec2(float x, float y);
    float x;
    float y;

    void zero();
    void one();
    void normalize();
    float distance(vec2 a, vec2 b);
};


#endif //VOXERRA_VEC2_H
