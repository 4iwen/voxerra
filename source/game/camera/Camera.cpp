#include "Camera.h"

Camera::Camera(Window* window, glm::vec3 position, float fov, float near, float far)
{
    this->window = window;
    this->position = position;
    this->fov = fov;
    this->nearPlane = near;
    this->farPlane = far;
}

void Camera::Update()
{
    ProcessMouseInputs();
    ProcessKeyboardInputs();

    int windowWidth, windowHeight;
    glfwGetWindowSize(window->window, &windowWidth, &windowHeight);
    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(fov),  (float)windowWidth / (float)windowHeight, nearPlane, farPlane);
    model = glm::mat4(1.0f);
    viewMatrix = projection * view * model;
}

void Camera::ProcessMouseInputs()
{
    if (showCursor)
        return;

    double mouseX, mouseY;
    glfwGetCursorPos(window->window, &mouseX, &mouseY);

    static bool firstMouse = true;
    static float lastX = 0.0f;
    static float lastY = 0.0f;

    if (firstMouse)
    {
        lastX = mouseX;
        lastY = mouseY;
        firstMouse = false;
    }

    float offsetX = mouseX - lastX;
    float offsetY = lastY - mouseY;
    lastX = mouseX;
    lastY = mouseY;

    offsetX *= sensitivity;
    offsetY *= sensitivity;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 tempFront;
    tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tempFront.y = sin(glm::radians(pitch));
    tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
}

void Camera::ProcessKeyboardInputs()
{
    if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        showCursor = true;
        glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        showCursor = false;
        glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window->window, &windowWidth, &windowHeight);
    }

    if (showCursor)
        return;

    if (glfwGetKey(window->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        speed = 0.3f;
    else
        speed = 0.1f;

    if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
        position += speed * front;
    if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
        position -= speed * front;
    if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * speed;
    if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * speed;

    if (glfwGetKey(window->window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += speed * up;
    if (glfwGetKey(window->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position -= speed * up;
}