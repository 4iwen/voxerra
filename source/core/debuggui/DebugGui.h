#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
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
    GLFWwindow* window;
    Camera* camera;
    bool vsync = true;
    int polygonMode = 0;
    float frameTimes[1000]{};
    bool showDemoWindow = false;
    ImVec4 clearColor = ImVec4(0.53f, 0.81f, 0.92f, 1.00f);

    static void SetStyle();
    void FrameTimesGraph();
};
