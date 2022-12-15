#pragma once

#include "glad/glad.h"

class VertexBuffer
{
public:
    unsigned int id;

    VertexBuffer();
    ~VertexBuffer();
    void bind();
    void unbind();
    void setData(const void* data, unsigned int size);
};