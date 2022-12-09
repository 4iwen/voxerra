#include "Window.h"

Window::Window(int windowWidth, int windowHeight, const char *windowName) {
    // initialize glfw
    if (!glfwInit()) {
        return;
    }

    // set window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // create window
    window = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // set window resize callback
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return;
    }

    // set opengl error callback
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(
            [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
               const void *userParam) {
                std::cout << "OpenGL Error: " << message << std::endl;
            }, nullptr);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
