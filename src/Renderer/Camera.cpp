#include "Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const Window& window) : m_window(window){

}

void Camera::moveForward(){
    heldY = true;
    velocity.y += 1.0f;
}

void Camera::moveBack(){
    heldY = true;
    velocity.y -= 1.0f;
}

void Camera::moveRight(){
    heldX = true;
    velocity.x += 1.0f;
}

void Camera::moveLeft(){
    heldX = true;
    velocity.x -= 1.0f;
}

void Camera::update(double deltaTime) {
    glm::normalize(velocity);
    velocity = velocity * (GLfloat)(deltaTime * ACCEL_RATE) * (1 + (FOV - FOV_MIN));

    if(!heldX){
        velocity.x += -velocity.x * DECCEL_RATE * deltaTime;
    }

    if(!heldY){
        velocity.y += -velocity.y * DECCEL_RATE * deltaTime;
    }

    heldX = false;
    heldY = false;

    position += velocity;
}

void Camera::zoomIn(){
    FOV -= 0.05f;

    if(FOV < FOV_MIN){
        FOV = FOV_MIN;
    }
}

void Camera::zoomOut(){
    FOV += 0.05f;

    if (FOV > FOV_MAX){
        FOV = FOV_MAX;
    }
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(FOV, m_window.width / (GLfloat)m_window.height, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() const {
    glm::vec3 worldLocation = glm::vec3(position, 0.01f);
    return glm::lookAt(worldLocation, worldLocation + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Top down
}