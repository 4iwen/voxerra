#include "vector"
#include "Vertex.h"
#include "glad/glad.h"
#include "../../../core/ElementBuffer.h"
#include "../../../core/VertexArray.h"
#include "../../../core/VertexBuffer.h"

class Mesh {
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Mesh();

    void Draw();

private:
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;
    unsigned int indicesIndex = 0;
};