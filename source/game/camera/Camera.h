#pragma once

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../../core/window/Window.h"
#include "GLFW/glfw3.h"

class Camera
{
public:
    Camera(GLFWwindow* window, glm::vec3 position, float fov, float near, float far);

    void Update();

    glm::vec3 position;
    //glm::mat4 viewMatrix;

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;

    float fov;
    float yaw = -90.0f;
    float pitch = 0.0f;

private:
    void ProcessMouseInputs();
    void ProcessKeyboardInputs();

    GLFWwindow* window;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

    float nearPlane;
    float farPlane;
    float sensitivity = 0.05f;
    float speed = 0.1f;
    bool showCursor = true;
};