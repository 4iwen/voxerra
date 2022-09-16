#include "glm/vec3.hpp"

class Camera {
public:
    Camera(glm::vec3 position, float fov, float near, float far);
    void Update();

private:
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);

    float yaw = 0.0f;
    float pitch = 0.0f;
    float fov = 90.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
};