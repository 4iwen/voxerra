#include "mesh.h"

Mesh::Mesh() {
    m_vbo.bind();
    m_vbo.setData(vertices.data(), vertices.size() * sizeof(float));

    m_ebo.bind();
    m_ebo.setData(indices.data(), indices.size() * sizeof(unsigned int));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_vao.unbind();
}

void Mesh::draw() {
    m_vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    m_vao.unbind();
}

void Mesh::addVertices(Vertex vertex, Vertex vertex1, Vertex vertex2, Vertex vertex3) {
    vertices.push_back(vertex.position.x);
    vertices.push_back(vertex.position.y);
    vertices.push_back(vertex.position.z);
    vertices.push_back(vertex.color.r);
    vertices.push_back(vertex.color.g);
    vertices.push_back(vertex.color.b);

    vertices.push_back(vertex1.position.x);
    vertices.push_back(vertex1.position.y);
    vertices.push_back(vertex1.position.z);
    vertices.push_back(vertex1.color.r);
    vertices.push_back(vertex1.color.g);
    vertices.push_back(vertex1.color.b);

    vertices.push_back(vertex2.position.x);
    vertices.push_back(vertex2.position.y);
    vertices.push_back(vertex2.position.z);
    vertices.push_back(vertex2.color.r);
    vertices.push_back(vertex2.color.g);
    vertices.push_back(vertex2.color.b);

    vertices.push_back(vertex3.position.x);
    vertices.push_back(vertex3.position.y);
    vertices.push_back(vertex3.position.z);
    vertices.push_back(vertex3.color.r);
    vertices.push_back(vertex3.color.g);
    vertices.push_back(vertex3.color.b);
}

void Mesh::addIndices() {
    indices.push_back(m_indicesIndex);
    indices.push_back(m_indicesIndex + 1);
    indices.push_back(m_indicesIndex + 2);
    indices.push_back(m_indicesIndex);
    indices.push_back(m_indicesIndex + 3);
    indices.push_back(m_indicesIndex + 1);
    m_indicesIndex += 4;
}