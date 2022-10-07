#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class DebugGui {
public:
    DebugGui(GLFWwindow* window);
    ~DebugGui();
    void Draw();
    ImVec4 GetClearColor();

private:
    bool _showDemoWindow = false;
    ImVec4 _clearColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

    static void SetStyle();
};
