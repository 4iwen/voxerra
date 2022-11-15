#pragma once

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