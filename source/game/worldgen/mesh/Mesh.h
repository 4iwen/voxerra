#include "vector"
#include "Vertex.h"
#include "../../../core/ElementBuffer.h"
#include "../../../core/VertexArray.h"
#include "../../../core/VertexBuffer.h"

class Mesh {
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Mesh();

    void Draw();

    void AddVertices(Vertex vertex, Vertex vertex1, Vertex vertex2, Vertex vertex3);

    void AddIndices();

private:
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;
    unsigned int indicesIndex = 0;
};