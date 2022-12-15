#pragma once

#include "glad/glad.h"

class VertexArray
{
public:
    unsigned int id;

    VertexArray();
    ~VertexArray();
    void bind();
    void unbind();
};