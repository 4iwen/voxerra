#include "iostream"
#include "fstream"

#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Shader.h"

// triangle vertices
float quadVertices[] = {
    //  x         y          z         r         g         b
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

};

// indices for the triangle above
unsigned int quadIndices[] = {
    0, 1, 2,
};

int main()
{
    // initialize glfw
    if(!glfwInit())
    {
        spdlog::error("Failed to initialize GLFW");
    }

    spdlog::info("Initialized GLFW, version: {0}", glfwGetVersionString());

    // set glfw error callback
    glfwSetErrorCallback([](int error, const char* description)
    {
        spdlog::error("GLFW Error: {0}", description);
    });

    // set opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "voxerra", nullptr, nullptr);
    if (window == nullptr)
    {
        spdlog::error("Failed to create window");
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
        spdlog::error("Failed to initialize glad");
        return -1;
    }

    spdlog::info("Initialized glad, OpenGL version: {0}.{1}", GLVersion.major, GLVersion.minor);

    // create vertex array object
    VertexArray vao;
    vao.Bind();

    // create vertex buffer object
    VertexBuffer vbo;
    vbo.Bind();
    vbo.SetData(quadVertices, sizeof(quadVertices));

    // create element buffer object
    ElementBuffer ebo;
    ebo.Bind();
    ebo.SetData(quadIndices, sizeof(quadIndices));

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind vertex array object
    vao.Unbind();

    // create shader program
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        glfwPollEvents();

        // clear screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        shader.Use();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        // swap buffers
        glfwSwapBuffers(window);
    }

    // terminate glfw
    glfwTerminate();

    return EXIT_SUCCESS;
}