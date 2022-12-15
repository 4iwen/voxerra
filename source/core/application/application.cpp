#include "application.h"

void Application::run() {
    m_window = new Window(1280, 720, "voxerra");
    m_camera = new Camera(m_window->window, glm::vec3(0.0f, 0.0f, 3.0f), 90.0f, 0.1f, 100.0f);
    m_gui = new Gui(m_window->window);
    m_chunkManager = new ChunkManager(157);
    m_blockShader = new Shader("shaders/block.vert", "shaders/block.frag");

    /*
    Window m_window(1280, 720, "voxerra");
    Camera* camera = new Camera(m_window.m_window, glm::vec3(0.0f, 0.0f, 3.0f), 90.0f, 0.1f, 100.0f);
    gui debugGui(m_window.m_window, camera);
    ChunkManager chunkManager(157);
    Shader blockShader("shaders/block.vert", "shaders/block.frag");
     */

    while (!m_window->shouldClose()) {
        m_window->pollEvents();
        m_window->setVsync(true);
        m_window->setClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        m_window->clear();

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


        m_camera->Update();
        m_blockShader->use();
        m_blockShader->setMat4("view", m_camera->view);
        m_blockShader->setMat4("projection", m_camera->projection);
        m_blockShader->setMat4("model", m_camera->model);
        m_chunkManager->update(1, 1, 8);
        //m_chunkManager->draw();
        m_gui->draw();
        m_window->swapBuffers();
    }
}