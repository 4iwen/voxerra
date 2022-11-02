#include "Camera.h"

Camera::Camera(GLFWwindow* window, glm::vec3 position, float fov, float near, float far)
{
    _window = window;
    _position = position;
    _fov = fov;
    _nearPlane = near;
    _farPlane = far;
}

void Camera::Update()
{
    ProcessMouseInputs();
    ProcessKeyboardInputs();

    int windowWidth, windowHeight;
    glfwGetWindowSize(_window, &windowWidth, &windowHeight);
    _view = glm::lookAt(_position, _position + _front, _up);
    _projection = glm::perspective(glm::radians(_fov),  (float)windowWidth / (float)windowHeight, _nearPlane, _farPlane);
}

void Camera::ProcessMouseInputs()
{
    if (_showCursor)
        return;

    double mouseX, mouseY;
    glfwGetCursorPos(_window, &mouseX, &mouseY);

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

    offsetX *= _sensitivity;
    offsetY *= _sensitivity;

    _yaw += offsetX;
    _pitch += offsetY;

    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);
}

void Camera::ProcessKeyboardInputs()
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        _showCursor = true;
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        _showCursor = false;
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        int windowWidth, windowHeight;
        glfwGetWindowSize(_window, &windowWidth, &windowHeight);
    }

    if (_showCursor)
        return;

    if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        _speed = 0.3f;
    else
        _speed = 0.1f;

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        _position += _speed * _front;
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        _position -= _speed * _front;
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        _position -= glm::normalize(glm::cross(_front, _up)) * _speed;
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        _position += glm::normalize(glm::cross(_front, _up)) * _speed;

    if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        _position += _speed * _up;
    if (glfwGetKey(_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        _position -= _speed * _up;
}

glm::mat4 Camera::GetView()
{
    return _view;
}

glm::mat4 Camera::GetProjection()
{
    return _projection;
}

float Camera::GetFov() const
{
    return _fov;
}

float Camera::GetPitch() const
{
    return _pitch;
}

float Camera::GetYaw() const
{
    return _yaw;
}

glm::vec3 Camera::GetPosition()
{
    return _position;
}