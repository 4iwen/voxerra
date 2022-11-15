#pragma once

class VertexArray
{
public:
    unsigned int ID;

    VertexArray();
    ~VertexArray();
    void Bind();
    void Unbind();
};