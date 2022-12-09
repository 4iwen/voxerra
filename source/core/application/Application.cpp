#include "Application.h"

void Application::Run() {
    Window window(1280, 720, "voxerra");
    Camera* camera = new Camera(window.window, glm::vec3(0.0f, 0.0f, 3.0f), 90.0f, 0.1f, 100.0f);
    DebugGui debugGui(window.window, camera);
    ChunkManager chunkManager(157);
    Shader blockShader("shaders/block.vert", "shaders/block.frag");

    while (!window.ShouldClose()) {
        window.PollEvents();

        // TODO: move all of this to a separate function(s)
        //glfwSwapInterval(debugGui.GetVsync());
        //glPolygonMode(GL_FRONT_AND_BACK, debugGui.GetPolygonMode());
        //// enable depth testing
        //glEnable(GL_DEPTH_TEST);
        //// enable face culling
        //glCullFace(GL_FRONT);
        //glFrontFace(GL_CCW);
        //// clear screen
        //ImVec4 clearColor = debugGui.GetClearColor();
        //glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.Clear();
        camera->Update();
        blockShader.Use();
        blockShader.SetMat4("view", camera->view);
        blockShader.SetMat4("projection", camera->projection);
        blockShader.SetMat4("model", camera->model);
        chunkManager.Update(1, 1, 8);
        chunkManager.Draw();
        debugGui.Draw();
        window.SwapBuffers();
    }
}