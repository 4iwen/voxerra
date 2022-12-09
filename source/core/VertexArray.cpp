#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::Bind()
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}