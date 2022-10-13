#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::Width = width;
    Camera::Height = height;
    Camera::Position = position;
}

void Camera::UpdateMatrix(float nearPlane, float farPlane)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    proj = glm::perspective(glm::radians(Fov), (float)(Width / Height), nearPlane, farPlane);

    CameraMatrix = proj * view;
}

void Camera::Matrix(Shader &shader, const char *uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(CameraMatrix   ));
}

void Camera::Inputs(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Position += Speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Position += Speed * Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Position += Speed * -Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Position += Speed * glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Position += Speed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        Position += Speed * -Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Speed = 0.4f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
    {
        Speed = 0.1f;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        // hide cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (FirstClick)
        {
            glfwSetCursorPos(window, (Width / 2), (Height / 2));
            FirstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = (Sensitivity * 100) * (float)(mouseY - (Width / 2)) / Width;
        float rotY = (Sensitivity * 100) * (float)(mouseX - (Height / 2)) / Height;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

        if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))))
        {
            Orientation = newOrientation;
        }

        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        glfwSetCursorPos(window, (Width / 2), (Height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        FirstClick = true;
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
}