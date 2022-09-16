#include "Camera.h"

Camera::Camera(glm::vec3 position, float fov, float near, float far)
{
    this->position = position;
    this->fov = fov;
    this->nearPlane = near;
    this->farPlane = far;
}

void Camera::Update()
{

}