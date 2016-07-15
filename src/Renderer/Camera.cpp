#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Camera.h"

glm::mat4 Camera::getViewMatrix() {
    glm::mat4 view;
    view = glm::rotate(view, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    return glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
}