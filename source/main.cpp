#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core/VertexArray.h"
#include "core/VertexBuffer.h"
#include "core/ElementBuffer.h"
#include "core/Shader.h"
#include "core/debuggui/DebugGui.h"
#include "game/Camera.h"
#include "core/FrameBuffer.h"
#include "worldgen/chunk.h"

// triangle vertices
float TESTvertices[] = {
    //  x         y          z         r         g         b
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

};

// indices for the triangle above
unsigned int TESTindices[] = {
    0, 1, 2,
};


int main()
{
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    std::cout << "before chunk" << std::endl;
    chunk chunk(32,512,32,0,0,noise);
    //std::cout << "after chunk" << std::endl;

    // initialize glfw
    glfwInit();

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
        return -1;
    }

    // create vertex array object
    VertexArray vao;
    vao.Bind();

    // create vertex buffer object
    VertexBuffer vbo;
    vbo.Bind();
    vbo.SetData(TESTvertices, sizeof(TESTvertices));

    // create element buffer object
    ElementBuffer ebo;
    ebo.Bind();
    ebo.SetData(TESTindices, sizeof(TESTindices));

    // TODO: implement frame buffer
    // create frame buffer object
    //FrameBuffer fbo;
    //fbo.Bind();

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind vertex array object
    vao.Unbind();

    // create shader program
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

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

        // clear screen
        ImVec4 clearColor = debugGui.GetClearColor();
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        camera.Update();
        shader.SetMat4("view", camera.GetView());
        shader.SetMat4("projection", camera.GetProjection());

        // draw
        shader.Use();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(TESTindices), GL_UNSIGNED_INT, nullptr);
        debugGui.Draw();


        // swap buffers
        glfwSwapBuffers(window);
    }

    // terminate glfw
    glfwTerminate();

    return EXIT_SUCCESS;
}