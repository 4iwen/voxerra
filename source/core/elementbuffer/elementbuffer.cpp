#include "elementbuffer.h"

ElementBuffer::ElementBuffer()
{
    glGenBuffers(1, &id);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &id);
}

void ElementBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::setData(const void* data, unsigned int size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
