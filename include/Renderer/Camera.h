#ifndef CAMERA_H
#define CAMERA_H

#include "Window.h"

class Camera {
    public:
        Camera(const Window& window);

        void moveForward();
        void moveLeft();
        void moveRight();
        void moveBack();
        void update(double deltaTime);

        void zoomIn();
        void zoomOut();

        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix();

        GLfloat FOV = 71.0f;

    private:
        const Window& m_window;

        glm::vec2 acceleration, velocity, position;
        bool heldX, heldY;

        const GLfloat ACCEL_RATE = 0.8f; //Default: 10.0f
        const GLfloat DECCEL_RATE = 0.8f; //Default: 8.0f

        const GLfloat FOV_MAX = 72.0f;
        const GLfloat FOV_MIN = 70.0f;
};

#endif