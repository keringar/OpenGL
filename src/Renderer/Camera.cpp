#include "Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

void Camera::moveForward() {
    yPosition += 0.5f;
}

void Camera::moveLeft() {
    xPosition += 0.5f;
}

void Camera::moveRight() {
    xPosition -= 0.5f;
}

void Camera::moveBack() {
    yPosition -= 0.5f;
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 worldLocation = glm::vec3(xPosition, yPosition, -5.0f);
    return glm::lookAt(worldLocation, worldLocation + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}