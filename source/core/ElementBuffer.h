#pragma once

#include "glad/glad.h"

class ElementBuffer
{
public:
    unsigned int ID;

    ElementBuffer();
    ~ElementBuffer();
    void Bind();
    void Unbind();
    void SetData(const void* data, unsigned int size);
};