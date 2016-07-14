#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Util.h"

#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>

class Window {
public:
    Window();
    ~Window();

    //Copy constructor
    Window(const Window& win);

    //Copy assignment
    Window& operator=(const Window& win);

    bool init();

    operator GLFWwindow*() const {
        return m_window;
    }

    bool isOpen() const;
    void close();
    void swap() const;

    glm::mat4 getProjectionMatrix(GLfloat fov) const;
private:
    GLFWwindow* m_window;
    Configuration m_config;

    static int width, height;
};

#endif