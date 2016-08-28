#include "Window.h"

Window::Window(EventDispatcher& dispatcher) : m_dispatcher{dispatcher}, m_config{"config"} {
    glfwSetErrorCallback(GLFWError);

    m_dispatcher.bind(EventType::TOGGLE_FULLSCREEN, [=](Data data){ this->toggleFullscreen(data); });
    m_dispatcher.bind(EventType::CLOSE, [=](Data data){ glfwSetWindowShouldClose(m_window, true); });
}

Window::~Window() {
    glfwTerminate();
}

bool Window::init() {
    //Get options from config file
    int windowX     = m_config.getAsInt("WindowSizeX");
    int windowY     = m_config.getAsInt("WindowSizeY");
    bool vsync      = m_config.getAsBool("V-Sync");
    bool fullscreen = m_config.getAsBool("Fullscreen");
    int MSAA        = m_config.getAsInt("MSAA");

    windowX = (windowX < 800 || windowX > 10000) ? std::stoi(m_config.setValue("WindowSizeX", "800")) : windowX;
    windowY = (windowY < 600 || windowY > 10000) ? std::stoi(m_config.setValue("WindowSizeY", "600")) : windowY;
    MSAA    = (MSAA < 0 || MSAA > 16) ? std::stoi(m_config.setValue("MSAA", "0")) : MSAA;

    if (glfwInit() == GLFW_FALSE) {
        Log::log("Failed to initialize windowing library");
        return false;
    }

    //OpenGL window options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, MSAA);

    m_window = glfwCreateWindow(windowX, windowY, "OpenGL", nullptr, nullptr);
    if (m_window == nullptr) {
        Log::log("Failed to create window");
        return false;
    }

    if (fullscreen) {
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
        glfwSetWindowSize(m_window, mode->width, mode->height);
    }

    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    setGLOptions();

    if (vsync) {
        glfwSwapInterval(1);
    }

    glfwSetWindowSizeLimits(m_window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetFramebufferSizeCallback(m_window, Window::GLFWWindowResize);
    glfwSetWindowUserPointer(m_window, this);

    //Send initial window size event for camera initialization
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    Window::GLFWWindowResize(m_window, width, height);

    return true;
}

bool Window::isOpen() const {
    return glfwWindowShouldClose(m_window) == GLFW_FALSE;
}

void Window::swap() const {
    glfwSwapBuffers(m_window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::toggleFullscreen(Data data) {
    if(!data.repeat) {
        if (m_config.getAsBool("Fullscreen")) {
            m_config.setValue("Fullscreen", "false");

            glfwSetWindowMonitor(m_window, nullptr, 100, 100, m_config.getAsInt("WindowSizeX"),
                                 m_config.getAsInt("WindowSizeY"), 0);
            glfwSetWindowSize(m_window, 100, 100);
        } else {
            m_config.setValue("Fullscreen", "true");

            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
            glfwSetWindowSize(m_window, mode->width, mode->height);
        }
    }
}

void Window::setGLOptions(){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Error callbacks
void Window::GLFWError(int error, const char *description) {
    Log::log(std::to_string(error));
    Log::log(description, Log::Channels::Error);
}

void Window::GLFWWindowResize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);

    Window* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));

    Data data;
    data.size.width = width;
    data.size.height = height;
    windowPtr->m_dispatcher.dispatch(EventType::RESIZE, data);
}