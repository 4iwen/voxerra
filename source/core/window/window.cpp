#include "window.h"

Window::Window(int windowWidth, int windowHeight, const char *windowName) {
    // initialize glfw
    if (!glfwInit()) {
        return;
    }

    // set m_window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // create m_window
    window = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // set m_window resize callback
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
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
        // the variables: type, id, severity are shown in numbers, not in words make them show in words
        std::string typeString;

        switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                typeString = "ERROR";
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                typeString = "DEPRECATED_BEHAVIOR";
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                typeString = "UNDEFINED_BEHAVIOR";
                break;
            case GL_DEBUG_TYPE_PORTABILITY:
                typeString = "PORTABILITY";
                break;
            case GL_DEBUG_TYPE_PERFORMANCE:
                typeString = "PERFORMANCE";
                break;
            case GL_DEBUG_TYPE_MARKER:
                typeString = "MARKER";
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP:
                typeString = "PUSH_GROUP";
                break;
            case GL_DEBUG_TYPE_POP_GROUP:
                typeString = "POP_GROUP";
                break;
            case GL_DEBUG_TYPE_OTHER:
                typeString = "OTHER";
                break;
        }

        std::string severityString;

        switch(severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                severityString = "HIGH";
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                severityString = "MEDIUM";
                break;
            case GL_DEBUG_SEVERITY_LOW:
                severityString = "LOW";
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                severityString = "NOTIFICATION";
                break;
        }

        std::cout << message << "\n";
        std::cout << "type: " << typeString << "\n";
        std::cout << "severity: " << severityString << "\n";
        std::cout << std::endl;

    }, nullptr);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Window::setVsync(bool vsync) {
    glfwSwapInterval(vsync);
}