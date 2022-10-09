#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "string"
#include "cmath"
#include "../../game/Camera.h"

class DebugGui {
public:
    DebugGui(GLFWwindow* window, Camera* camera);
    ~DebugGui();
    void Draw();
    ImVec4 GetClearColor();
    int GetPolygonMode() const;
    int GetVsync() const;

private:
    GLFWwindow* _window;
    Camera* _camera;
    bool _vsync = true;
    int _polygonMode = 0;
    float _frames[240]{};
    bool _showDemoWindow = false;
    ImVec4 _clearColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

    static void SetStyle();
    void FpsGraph();
};
