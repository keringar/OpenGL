#include "Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

Camera::Camera(EventDispatcher& dispatcher) : m_dispatcher{dispatcher}{
    m_dispatcher.bind(EventType::RESIZE, [=](Data data){ resizeCallback(data); });
    m_dispatcher.bind(EventType::MOVE_UP, [=](Data data){ moveForward(); });
    m_dispatcher.bind(EventType::MOVE_RIGHT, [=](Data data){ moveRight(); });
    m_dispatcher.bind(EventType::MOVE_DOWN, [=](Data data){ moveBack(); });
    m_dispatcher.bind(EventType::MOVE_LEFT, [=](Data data){ moveLeft(); });
    m_dispatcher.bind(EventType::ZOOM_IN, [=](Data data){ zoomIn(); });
    m_dispatcher.bind(EventType::ZOOM_OUT, [=](Data data){ zoomOut(); });
}

void Camera::setPosition(float x, float y) {
    this->position.x = x;
    this->position.y = y;

    checkWithinLimits();
}

void Camera::setLimits(int x, int y) {
    MAX_DIST_X = x;
    MAX_DIST_Y = y;
}

void Camera::resizeCallback(Data data) {
    window_width = data.size.width;
    window_height = data.size.height;
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
    //Zoom
    ZOOM += desiredZoom * deltaTime * ZOOM_SENSITIVITY;
    ZOOM = glm::clamp(ZOOM, ZOOM_MIN, ZOOM_MAX);
    desiredZoom = 0.0f;

    //Scrolling
    GLfloat scrollSpeed = (1 + ((ZOOM - ZOOM_MIN) / ZOOM_MAX)) * 3; //3 is scroll speed basically
    glm::normalize(velocity);
    velocity = velocity * (GLfloat)(deltaTime * scrollSpeed);
    velocity.x += (!heldX) ? -velocity.x * deltaTime * scrollSpeed : 0;
    velocity.y += (!heldY) ? -velocity.y * deltaTime * scrollSpeed : 0;

    heldX = false;
    heldY = false;

    position += velocity;

    checkWithinLimits();
}

void Camera::zoomIn() {
    desiredZoom = -1.5f;
}

void Camera::zoomOut() {
    desiredZoom = 1.5f;
}

//Only good when width > height
glm::mat4 Camera::getProjectionMatrix() {
    GLfloat aspectratio = (GLfloat)window_width / window_height;
    return glm::ortho(-aspectratio * ZOOM, aspectratio * ZOOM, -ZOOM, ZOOM, 1.0f, 3.0f);
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 worldLocation = glm::vec3(position, 1.0f);
    return glm::lookAt(worldLocation, worldLocation + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Top down
}