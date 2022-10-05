#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "Chunk.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "FastNoiseLite.h"
#include "WeaponClass.h"
#include "enums.h"


// screen
const unsigned int width = 800;
const unsigned int height = 800;

// chunk ?
Chunk chunk;
const unsigned int chunkWidth = 4;
const unsigned int chunkLength = 4;
const unsigned int chunkHeight = 16;

FastNoiseLite noise;

// cube
GLfloat testVertices[] =
{
    -0.5f, -0.5f, 0.0f, 0.7f, 0.6f, 0.84f,
    0.5f, -0.5f, 0.0f, 0.6f, 0.5f, 0.74f,
    -0.5f, 0.5f, 0.0f, 0.5f, 0.4f, 0.64f,
    0.5f, 0.5f, 0.0f, 0.4f, 0.3f, 0.54f,
    -0.5f, -0.5f, -1.0f, 0.3f, 0.2f, 0.44f,
    0.5f, -0.5f, -1.0f, 0.2f, 0.1f, 0.34f,
    -0.5f, 0.5f, -1.0f, 0.1f, 0.0f, 0.24f,
    0.5f, 0.5f, -1.0f, 0.0f, 0.1f, 0.14f,
};

GLuint testIndices[] =
{
        // top
        2, 6, 7,
        2, 3, 7,

        // bottom
        0, 4, 5,
        0, 1, 5,

        // left
        0, 2, 6,
        0, 4, 6,

        // right
        1, 3, 7,
        1, 5, 7,

        // front
        0, 2, 3,
        0, 1, 3,

        // back
        4, 6, 7,
        4, 5, 7
};

int main()
{
    WeaponClass weapon(30,30,30,30,30,3,Sword, "Swrd","Nods");
    //cout << "Damage dealt was : " << weapon.GetDamage(200) <<endl;

    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetSeed(1337);
    noise.SetFrequency(0.01f);

    chunk.GenerateChunk(noise, 1, 1, 4, 4, 16);

    // Create a vector of integers
    vector<GLfloat> *verticesVec = chunk.ReturnVerticies();
    vector<GLuint> *indicesVec = chunk.ReturnIndecies();

    GLfloat vertices[chunk.ReturnVerticiesSize()];
    GLuint indices[chunk.ReturnIndeciesSize()];

    for (int i = 0; i < chunk.ReturnIndeciesSize(); i++) {
        indices[i] = indicesVec->at(i);
    }

    for (int v = 0; v < chunk.ReturnVerticiesSize(); v++) {
        vertices[v] = verticesVec->at(v);
    }

    cout << chunk.ReturnIndeciesSize() << endl;
    cout << sizeof(indices) << endl;
    cout << chunk.ReturnVerticiesSize() << endl;
    cout << sizeof(vertices) << endl;

    // initialize glfw
    if (!glfwInit())
    {
        std::cout << "Failed to create initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    // window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window
    GLFWwindow* window = glfwCreateWindow(width, height, "voxerra", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    Shader shaderProgram(".\\shaders\\default.vert", ".\\shaders\\default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), nullptr);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    float rotation = 0.0f;
    double previousTime = glfwGetTime();
    glfwSwapInterval(1);
    // main loop
    while (!glfwWindowShouldClose(window))
    {
        // clear whole window with set color
        glClearColor(0.725f, 0.87f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw
        shaderProgram.Activate();

        double currentTime = glfwGetTime();
        if (currentTime - previousTime >= 1 / 60)
        {
            rotation += 0.5f;
            previousTime = currentTime;
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.1f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -5.0f, -10.0f));
        proj = glm::perspective(glm::radians(80.0f), (float)(width / height), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glad_glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glad_glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glad_glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glad_glUniform1f(uniID, 1);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, chunk.ReturnIndeciesSize(), GL_UNSIGNED_INT, nullptr);

        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        // swap buffers
        glfwSwapBuffers(window);
        // poll events
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}