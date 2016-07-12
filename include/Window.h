#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Util.h"

class Window {
public:
    Window();

    ~Window();

    bool init();

    operator GLFWwindow *() const {
        return m_window;
    }

    bool isOpen();

    void close();

private:
    GLFWwindow *m_window;
    Configuration m_config;
};

#endif