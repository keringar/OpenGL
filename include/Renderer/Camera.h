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

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

        void setPosition(glm::vec3 position);
        void setLimits(int height, int width);

    private:
        void checkWithinLimits();

        const Window& m_window;

        glm::vec2 acceleration, velocity, position;
        bool heldX, heldY;

        const GLfloat ACCEL_RATE = 5.0f; //Default: 10.0f

        GLfloat ZOOM = 10.0f;
        GLfloat ZOOM_MAX = 100.0f;
        GLfloat ZOOM_MIN = 1.0f;

        //Max distance from origin that camera can move
        GLint MAX_DIST_Y = 0;
        GLint MAX_DIST_X = 0;
};

#endif