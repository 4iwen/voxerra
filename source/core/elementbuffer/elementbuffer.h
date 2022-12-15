#pragma once

#include "glad/glad.h"

class ElementBuffer
{
public:
    unsigned int id;

    ElementBuffer();
    ~ElementBuffer();
    void bind();
    void unbind();
    void setData(const void* data, unsigned int size);
};