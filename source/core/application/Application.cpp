#include "Application.h"

Application::Application(bool debug) {
    window = new Window(1280, 720, "voxerra");
    camera = new Camera(window, glm::vec3(0.0f, 0.0f, 3.0f), 90.0f, 0.1f, 100.0f);

    if (debug) {
        debugGui = new DebugGui(window->window, camera);
    }

    chunkManager = new ChunkManager(157);
}

Application::~Application() {
    delete window;
}

void Application::Run() {
    while (!window->ShouldClose()) {
        window->PollEvents();

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
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window->Clear();
        camera->Update();
        chunkManager->Update(0, 0, 8);
        chunkManager->Draw();

        if (debugGui) {
            debugGui->Draw();
        }

        window->SwapBuffers();
    }
}