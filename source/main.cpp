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
#include "game/chunk/ChunkManager.h"

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

void CheckGLError();

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

    // opengl error checker


    // generate chunks
    std::vector<Chunk*> chunks;
    ChunkManager chunkManager;
    chunkManager.GenerateChunks(8,  8);
    std::cout << "generated chunks" << std::endl;
    chunkManager.GetChunks(chunks);
    std::vector<float> worldVertices;
    std::vector<unsigned int> worldIndices;

    for (Chunk* chunk : chunks)
    {
        std::vector<float> chunkVertices;
        std::vector<unsigned int> chunkIndices;
        chunk->GetVertices(chunkVertices);
        chunk->GetIndices(chunkIndices);

        worldVertices.insert(worldVertices.end(), chunkVertices.begin(), chunkVertices.end());
        worldIndices.insert(worldIndices.end(), chunkIndices.begin(), chunkIndices.end());
    }

    std::cout << "vertices length: " << worldVertices.size() << std::endl;
    std::cout << "indices length: " << worldIndices.size() << std::endl;

    // create vertex array object
    VertexArray vao;
    vao.Bind();

    // create vertex buffer object
    VertexBuffer vbo;
    vbo.Bind();
    vbo.SetData(worldVertices.data(), worldVertices.size() * sizeof(float));

    // create element buffer object
    ElementBuffer ebo;
    ebo.Bind();
    ebo.SetData(worldIndices.data(), worldIndices.size() * sizeof(unsigned int));

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
        shader.SetMat4("model", glm::mat4(1.0f));

        // draw
        shader.Use();
        vao.Bind();

        // draw the generated chunks
        glDrawElements(GL_TRIANGLES, worldIndices.size(), GL_UNSIGNED_INT, 0);

        // unbind vertex array object
        vao.Unbind();

        // draw debug gui
        debugGui.Draw();

        // check for gl errors
        CheckGLError();

        // swap buffers
        glfwSwapBuffers(window);
    }

    // terminate glfw
    glfwTerminate();
    return 0;
}

void CheckGLError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
    }
}
