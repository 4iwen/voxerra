#include "Vertex.h"

Vertex::Vertex(glm::vec3 position, glm::vec3 color) {
    _position = position;
    _color = color;
}

glm::vec3 Vertex::GetPosition() {
    return _position;
}

glm::vec3 Vertex::GetColor() {
    return _color;
}
