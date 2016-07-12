#include "Window.h"

void GLFWError(int error, const char *description) {
    Log::log(description, Log::Channels::Error);
}

Window::Window() : m_config{"config"} {

}

Window::~Window() {
    glfwTerminate();
}

//Copy constructor
Window::Window(const Window& win) : m_config{"config"} {
    this->m_window = win.m_window;
}

//Copy assignment operator
Window& Window::operator=(const Window& win) {
    this->m_window = win.m_window;
    this->m_config = win.m_config;
    return *this;
}

bool Window::init() {
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int windowX = m_config.getAsInt("WindowSizeX");
    int windowY = m_config.getAsInt("WindowSizeY");
    bool vsync = m_config.getAsBool("V-Sync");
    bool fullscreen = m_config.getAsBool("Fullscreen");

    if (windowX < 800 || windowX > 10000) {
        windowX = std::stoi(m_config.setValue("WindowSizeX", "800"));
    }

    if (windowY < 600 || windowY > 10000) {
        windowY = std::stoi(m_config.setValue("WindowSizeY", "600"));
    }

    if (glfwInit() == GLFW_FALSE) {
        Log::log("Failed to initialize OpenGL library");
        return false;
    }

    m_window = glfwCreateWindow(windowX, windowY, "OpenGL", nullptr, nullptr);

    if (m_window == nullptr) {
        Log::log("Failed to create window");
        return false;
    }

    if (fullscreen) {
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    if (vsync) {
        glfwSwapInterval(1);
    }

    glfwSetWindowSizeLimits(m_window, 800, 600, 100000, 100000);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwMakeContextCurrent(m_window);
    glfwSetErrorCallback(GLFWError);

    return true;
}

bool Window::isOpen() {
    return glfwWindowShouldClose(m_window) == GLFW_FALSE;
}

void Window::close() {
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}