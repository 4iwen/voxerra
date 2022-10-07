#include "ElementBuffer.h"

#include "glad/glad.h"

ElementBuffer::ElementBuffer()
{
    glGenBuffers(1, &ID);
    //spdlog::info("Created Element Buffer with ID: {0}", ID);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &ID);
    //spdlog::info("Deleted Element Buffer with ID: {0}", ID);
}

void ElementBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::SetData(const void* data, unsigned int size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
