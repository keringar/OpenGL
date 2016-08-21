#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Util.h"
#include "Input/Input.h"

class Input;

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
    void toggleFullscreen();

    void pollEvents();
    bool getEvent(Event& event);

    static int width, height;

private:
    void setGLOptions();

    GLFWwindow* m_window;
    Configuration m_config;
    Input m_input;
};

#endif