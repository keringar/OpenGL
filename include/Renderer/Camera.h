#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>
#include "EventDispatcher.h"

class Camera {
    public:
        Camera(EventDispatcher &dispatcher);

        void update(double deltaTime);

        void moveForward();
        void moveLeft();
        void moveRight();
        void moveBack();
        void zoomIn();
        void zoomOut();

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

        //Based on tiles
        void setPosition(float x, float y);
        void setLimits(int x, int y);

    private:
        void checkWithinLimits();

        void resizeCallback(Data data);

        glm::vec2 acceleration, velocity, position;
        bool heldX, heldY;
        EventDispatcher &m_dispatcher;

        GLfloat desiredZoom;
        GLfloat ZOOM_SENSITIVITY = 100.0f;
        GLfloat ZOOM = 10.0f;
        GLfloat ZOOM_MAX = 100.0f;
        //GLfloat ZOOM_MIN = 10.0f;
        GLfloat ZOOM_MIN = 1.0f;

        //Max distance from origin that camera can move in pixels
        GLint MAX_DIST_Y = 0;
        GLint MAX_DIST_X = 0;

        GLint window_width;
        GLint window_height;
};

#endif