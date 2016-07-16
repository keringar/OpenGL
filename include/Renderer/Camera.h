#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>

class Camera {
    public:
        void moveForward();
        void moveLeft();
        void moveRight();
        void moveBack();
        void update(double deltaTime);

        glm::mat4 getViewMatrix();

    private:
        glm::vec2 acceleration, velocity, position;
        bool heldX, heldY;

        const GLfloat ACCEL_RATE = 1.5f;  //Default:  0.8f
        const GLfloat DECCEL_RATE = 10.0f;//Default: 10.0f
};

#endif