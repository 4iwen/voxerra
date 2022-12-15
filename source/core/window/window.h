#pragma once

#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window {

public:
    Window(int windowWidth, int windowHeight, const char *windowName);

    ~Window();

    bool shouldClose();

    void swapBuffers();

    void pollEvents();

    void clear();

    void setClearColor(float r, float g, float b, float a);

    void setVsync(bool vsync);

    GLFWwindow *window;
};
