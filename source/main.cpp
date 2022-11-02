#include <vector>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core/VertexArray.h"
#include "core/VertexBuffer.h"
#include "core/ElementBuffer.h"
#include "core/Shader.h"
#include "core/debuggui/DebugGui.h"
#include "game/Camera/Camera.h"
#include "FastNoiseLite/FastNoiseLite.h"
#include "game/chunk/Chunk.h"

// cube vertices
float vertices[] = {
    //  x         y          z
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
};

// indices for the cube above
unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

int main()
{
    // initialize glfw
    if (!glfwInit())
    {
        return -1;
    }

    // set opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "voxerra", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // set window resize callback
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    // create vertex array object
    VertexArray vao;
    vao.Bind();

    // create vertex buffer object
    VertexBuffer vbo;
    vbo.Bind();
    vbo.SetData(vertices, sizeof(vertices));

    // create element buffer object
    ElementBuffer ebo;
    ebo.Bind();
    ebo.SetData(indices, sizeof(indices));

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind vertex array object
    vao.Unbind();

    // cube shader
    Shader shader("shaders/cube.vert", "shaders/cube.frag");
    // light shader
    Shader lightShader("shaders/light.vert", "shaders/light.frag");

    // create camera
    Camera camera(window, glm::vec3(0.0f, 0.0f, 3.0f), 90.0f, 0.1f, 100.0f);

    // create debug gui
    DebugGui debugGui(window, &camera);

    Chunk chunk(0, 0);
    chunk.Generate();
    chunk.GenerateVerticesAndIndices();

    std::vector<float> chunkVertices;
    std::vector<unsigned int> chunkIndices;
    chunk.GetVertices(chunkVertices);
    chunk.GetIndices(chunkIndices);

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        glfwPollEvents();

        // set render settings
        glfwSwapInterval(debugGui.GetVsync());
        glPolygonMode(GL_FRONT_AND_BACK, debugGui.GetPolygonMode());
        // enable depth testing
        glEnable(GL_DEPTH_TEST);
        // enable face culling
        glCullFace(GL_FRONT);
        glFrontFace(GL_CCW);
        // clear screen
        ImVec4 clearColor = debugGui.GetClearColor();
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update();
        shader.SetMat4("view", camera.GetView());
        shader.SetMat4("projection", camera.GetProjection());
        //switch (chunk.GetChunkData()) {
//
        //}
        shader.SetVec3("blockColor", glm::vec3(0.15f, 0.65f, 0.15f));

        // draw
        shader.Use();
        vao.Bind();

        // draw the generated chunk with the vertices and indices from the chunk



        //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, nullptr);
        debugGui.Draw();

        // swap buffers
        glfwSwapBuffers(window);
    }

    // terminate glfw
    glfwTerminate();

    return 0;
}