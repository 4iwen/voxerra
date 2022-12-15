#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "string"
#include "cmath"
#include "../../game/Camera/camera.h"

class Gui {
public:
    Gui(GLFWwindow* window);
    ~Gui();
    void draw();

private:
    GLFWwindow* m_window;
    bool m_showDemoWindow = false;
};
