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

    private:
        const Window& m_window;

        glm::vec2 acceleration, velocity, position;
        bool heldX, heldY;

        const GLfloat ACCEL_RATE = 10.0f; //Default: 10.0f
        const GLfloat DECCEL_RATE = 8.0f; //Default: 8.0f

        GLfloat ZOOM = 52.5f;
        const GLfloat ZOOM_MAX = 100.0f;
        const GLfloat ZOOM_MIN = 5.0f;
};

#endif