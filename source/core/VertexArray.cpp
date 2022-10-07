#include "VertexArray.h"

#include "glad/glad.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);

    //spdlog::info("Created Vertex Array with ID: {0}", ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);

    //spdlog::info("Deleted Vertex Array with ID: {0}", ID);
}

void VertexArray::Bind()
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::SetAttribute()
{

}