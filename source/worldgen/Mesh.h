#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../core/Shader.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4


struct Vertex {

    Vertex(glm::vec3 Position, glm::vec3 Color) {this->Position = Position; this->Color = Color;}

    glm::vec3 Position;
    glm::vec3 Color;
};

class Mesh {
public:
    vector<Vertex> vertices;
    int vertices_size;
    vector<unsigned int> indices;
    unsigned int VAO;

    Mesh() { setupMesh(); }

    Mesh(vector<Vertex> vertices);

    void Draw(Shader& shader);

    void updateMesh() ;

    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
private:
    unsigned int VBO, EBO;
    void setupMesh();
};