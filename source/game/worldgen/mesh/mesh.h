#include "vector"
#include "vertex.h"
#include "../../../core/elementbuffer/elementbuffer.h"
#include "../../../core/vertexarray/vertexarray.h"
#include "../../../core/vertexbuffer/vertexbuffer.h"

class Mesh {
public:
    Mesh();

    void draw();

    void addVertices(Vertex vertex, Vertex vertex1, Vertex vertex2, Vertex vertex3);

    void addIndices();

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

private:
    VertexArray m_vao;
    VertexBuffer m_vbo;
    ElementBuffer m_ebo;
    unsigned int m_indicesIndex = 0;
};