#include "Mesh.h"
using namespace std;
    Mesh::Mesh(vector<Vertex> vertices)
    {
        this->vertices = vertices;

        setupMesh();
    }

    void Mesh::Draw(Shader& shader)
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices_size);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
    }

    void Mesh::updateMesh() {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        vertices_size = vertices.size();
    }


    void Mesh::setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // vertex Color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    }


}
