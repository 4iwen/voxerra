#pragma once

#include "glad/glad.h"

class VertexBuffer
{
public:
    unsigned int ID;

    VertexBuffer();
    ~VertexBuffer();
    void Bind();
    void Unbind();
    void SetData(const void* data, unsigned int size);
};