#pragma once

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GLFW/glfw3.h"
#include "../../core/window/Window.h"

class Camera
{
public:
    Camera(Window* window, glm::vec3 position, float fov, float near, float far);
    void Update();

    glm::mat4 viewMatrix;

    float fov;
    float yaw = -90.0f;
    float pitch = 0.0f;

private:
    void ProcessMouseInputs();
    void ProcessKeyboardInputs();

    Window* window;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

    glm::vec3 position;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;

    float nearPlane;
    float farPlane;
    float sensitivity = 0.05f;
    float speed = 0.1f;
    bool showCursor = true;
};