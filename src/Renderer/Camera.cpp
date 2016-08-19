#include "Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const Window& window) : m_window(window){

}

void Camera::setLimits(int originX, int originY, int height, int width) {
    MAX_DIST_X = width;
    MAX_DIST_Y = height;
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
    checkWithinLimits();
}

void Camera::checkWithinLimits(){
    if(position.x < 0 && position.x < MAX_DIST_X){
        position.x = 0;
    }

    if(position.x > MAX_DIST_X && position.x > 0){
        position.x = MAX_DIST_X;
    }

    if(position.y < 0 && position.y < MAX_DIST_Y){
        position.y = 0;
    }

    if(position.y > MAX_DIST_Y && position.y > 0){
        position.y = MAX_DIST_Y;
    }
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
    GLfloat zoomFactor = (0.2f / (1 - (ZOOM / ZOOM_MAX)));
    zoomFactor = std::min(zoomFactor, 4.0f);
    zoomFactor = zoomFactor < 1 ? 1 : zoomFactor;

    glm::normalize(velocity);
    velocity = velocity * (GLfloat)(deltaTime * ACCEL_RATE * zoomFactor);

    if(!heldX){
        velocity.x += -velocity.x * ACCEL_RATE * deltaTime * zoomFactor;
    }

    if(!heldY){
        velocity.y += -velocity.y * ACCEL_RATE * deltaTime * zoomFactor;
    }

    heldX = false;
    heldY = false;

    position += velocity;

    checkWithinLimits();
}

void Camera::zoomIn(){
    ZOOM -= 0.5f;

    if(ZOOM < ZOOM_MIN){
        ZOOM = ZOOM_MIN;
    }
}

void Camera::zoomOut(){
    ZOOM += 0.5f;

    if(ZOOM > ZOOM_MAX){
        ZOOM = ZOOM_MAX;
    }
}

//Only good when width > height
glm::mat4 Camera::getProjectionMatrix() {
    GLfloat aspectratio = (GLfloat)m_window.width / m_window.height;
    return glm::ortho(-aspectratio * ZOOM, aspectratio * ZOOM, -1.0f * ZOOM, 1.0f * ZOOM, 1.0f, 3.0f);
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 worldLocation = glm::vec3(position, 1.0f);
    return glm::lookAt(worldLocation, worldLocation + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Top down
}