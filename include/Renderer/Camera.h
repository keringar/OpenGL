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

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

        //Based on tiles
        void setPosition(float x, float y);
        void setLimits(int x, int y);

    private:
        void moveForward();
        void moveLeft();
        void moveRight();
        void moveBack();
        void zoomIn();
        void zoomOut();

        void checkWithinLimits();

        void resizeCallback(Data data);

        EventDispatcher &m_dispatcher;
        glm::vec2 acceleration, velocity, position;
        bool heldX = false;
        bool heldY = false;

        GLfloat desiredZoom = 10.0f;
        GLfloat ZOOM_SENSITIVITY = 100.0f;
        GLfloat ZOOM = 10.0f;
        const GLfloat ZOOM_MAX = 100.0f;
        const GLfloat ZOOM_MIN = 10.0f;

        //Max distance from origin that camera can move in pixels
        GLint MAX_DIST_Y = 0;
        GLint MAX_DIST_X = 0;

        GLint window_width = 0;
        GLint window_height = 0;
};

#endif