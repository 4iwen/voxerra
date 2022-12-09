#pragma once

#include "glad/glad.h"

class VertexArray
{
public:
    unsigned int ID;

    VertexArray();
    ~VertexArray();
    void Bind();
    void Unbind();
};