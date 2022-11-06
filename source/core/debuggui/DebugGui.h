#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "string"
#include "cmath"
#include "../../game/Camera/Camera.h"

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
    float _frames[300]{};
    bool _showDemoWindow = false;
    // sky blue
    ImVec4 _clearColor = ImVec4(0.53f, 0.81f, 0.92f, 1.00f);

    static void SetStyle();
    void FpsGraph();
};
