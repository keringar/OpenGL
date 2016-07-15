#ifndef CAMERA_H
#define CAMERA_H

#include <glm/detail/type_mat.hpp>

class Camera {
    public:
        void moveForward();
        void moveLeft();
        void moveRight();
        void moveBack();

        glm::mat4 getViewMatrix();

    private:

};

#endif