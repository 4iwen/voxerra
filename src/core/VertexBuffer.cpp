#include "VertexBuffer.h"

#include "spdlog/spdlog.h"
#include "glad/glad.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);

    spdlog::info("Created Vertex Buffer with ID: {0}", ID);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);

    spdlog::info("Deleted Vertex Buffer with ID: {0}", ID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, unsigned int size)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}