#include "Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

void Camera::moveForward(){
    heldY = true;
    acceleration.y += 1.0f;
}

void Camera::moveBack(){
    heldY = true;
    acceleration.y -= 1.0f;
}

void Camera::moveRight(){
    heldX = true;
    acceleration.x += 1.0f;
}

void Camera::moveLeft(){
    heldX = true;
    acceleration.x -= 1.0f;
}

#include "Util.h"
void Camera::zoom(double zoomOffset){
    Log::log(std::to_string(zoomOffset));
}

void Camera::update(double deltaTime) {
    glm::normalize(acceleration);
    acceleration *= ACCEL_RATE * deltaTime;

    velocity += acceleration;
    glm::clamp(velocity, 0.0f, 0.1f);

    position += velocity;

    if(!heldX){
        velocity.x += -velocity.x * DECCEL_RATE * deltaTime;
    }

    if(!heldY){
        velocity.y += -velocity.y * DECCEL_RATE * deltaTime;
    }

    heldX = false;
    heldY = false;
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 worldLocation = glm::vec3(position, 5.0f);
    return glm::lookAt(worldLocation, worldLocation + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Top down
}