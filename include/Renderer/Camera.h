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

        glm::mat4 getViewMatrix();

    private:
        GLfloat xPosition = 0;
        GLfloat yPosition = 0;
};

#endif