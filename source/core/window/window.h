#pragma once

#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec3.hpp"

class Window {

public:
    Window(int windowWidth, int windowHeight, const char *windowName);

    ~Window();

    bool shouldClose();

    void swapBuffers();

    void pollEvents();

    void clear(glm::vec3 color);

    void setVsync(bool vsync);

    GLFWwindow *window;
};
