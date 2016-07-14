#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Camera.h"

glm::mat4 Camera::getViewMatrix() {
    glm::mat4 view;
    return glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
}