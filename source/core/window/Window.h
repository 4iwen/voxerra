#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "iostream"

class Window {

public:
    Window(int windowWidth, int windowHeight, const char *windowName);

    ~Window();

    bool ShouldClose();

    void SwapBuffers();

    void PollEvents();

    GLFWwindow *window;

    void Clear();
};
