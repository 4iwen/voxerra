#pragma once

#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window {

public:
    Window(int windowWidth, int windowHeight, const char *windowName);

    ~Window();

    bool ShouldClose();

    void SwapBuffers();

    void PollEvents();

    void Clear();

    GLFWwindow *window;
};
