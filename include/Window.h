#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EventDispatcher.h"
#include "Util.h"

class Input;

class Window {
public:
    //Constructor
    Window(EventDispatcher& dispatcher);
    //Destructor
    ~Window();
    //Copy constructor
    Window(const Window& win);
    //Copy assignment
    Window& operator=(const Window& win);
    //Automatic type conversion for glfw
    operator GLFWwindow*() const {
        return m_window;
    }

    bool init();

    bool isOpen() const;
    void swap() const;

private:
    void setGLOptions();
    void toggleFullscreen(Data data);

    static void GLFWError(int error, const char* description);
    static void GLFWWindowResize(GLFWwindow* window, int width, int height);

    GLFWwindow* m_window;
    EventDispatcher& m_dispatcher;
    Configuration m_config;
};

#endif