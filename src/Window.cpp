#include "Window.h"

//Initialize static variables
int Window::width = 0;
int Window::height = 0;

void GLFWError(int error, const char *description) {
    Log::log(std::to_string(error));
    Log::log(description, Log::Channels::Error);
}

void framebufferResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;
}

void Window::pollEvents() {
    m_input.update();
}

void Window::setGLOptions(){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool Window::getEvent(Event& event) {
    if(!m_input.eventQueue.empty()){
        auto currentEvent = m_input.eventQueue.back();

        //Copy everything because vector.back returns a direct reference which gets in the way of deleting last element
        event.type = currentEvent.type;
        event.repeat = currentEvent.repeat;

        if(event.type == Event::GAME){
            event.game.type = currentEvent.game.type;
        } else if(event.type == Event::MOUSE){
            event.mouse.x = currentEvent.mouse.x;
            event.mouse.y = currentEvent.mouse.y;
        } else if(event.type == Event::RESIZE){
            event.size.height = currentEvent.size.height;
            event.size.width = currentEvent.size.width;
        }

        m_input.eventQueue.pop_back();

        return true;
    }

    return false;
}

Window::Window() : m_config{"config"}, m_input{m_window}{
    glfwSetErrorCallback(GLFWError);
}

Window::~Window() {
    glfwTerminate();
}

//Copy constructor
Window::Window(const Window& win) : m_config{"config"}, m_input{m_window} {
    this->m_window = win.m_window;
}

//Copy assignment operator
Window& Window::operator=(const Window& win) {
    this->m_window = win.m_window;
    this->m_config = win.m_config;
    return *this;
}

bool Window::init() {
    int windowX = m_config.getAsInt("WindowSizeX");
    int windowY = m_config.getAsInt("WindowSizeY");
    bool vsync = m_config.getAsBool("V-Sync");
    bool fullscreen = m_config.getAsBool("Fullscreen");
    int MSAA_sample = m_config.getAsInt("MSAA");

    if (windowX < 800 || windowX > 10000) {
        windowX = std::stoi(m_config.setValue("WindowSizeX", "800"));
    }

    if (windowY < 600 || windowY > 10000) {
        windowY = std::stoi(m_config.setValue("WindowSizeY", "600"));
    }

    if (MSAA_sample < 0 || MSAA_sample > 16) {
        MSAA_sample = std::stoi(m_config.setValue("MSAA", "0"));
    }

    if (glfwInit() == GLFW_FALSE) {
        Log::log("Failed to initialize OpenGL library");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, MSAA_sample);

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

    if (vsync) {
        glfwSwapInterval(1);
    }

    glfwSetWindowSizeLimits(m_window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetFramebufferSizeCallback(m_window, framebufferResize);
    glfwGetFramebufferSize(m_window, &Window::width, &Window::height);

    setGLOptions();

    m_input = Input(m_window);

    return true;
}

bool Window::isOpen() const {
    return glfwWindowShouldClose(m_window) == GLFW_FALSE;
}

void Window::close() {
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void Window::swap() const {
    glfwSwapBuffers(m_window);
}

void Window::toggleFullscreen() {
    if(m_config.getAsBool("Fullscreen")){
        m_config.setValue("Fullscreen", "false");

        glfwSetWindowMonitor(m_window, nullptr, 100, 100, m_config.getAsInt("WindowSizeX"), m_config.getAsInt("WindowSizeY"), 0);
        glfwSetWindowSize(m_window, 100, 100);
    } else {
        m_config.setValue("Fullscreen", "true");

        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
        glfwSetWindowSize(m_window, mode->width, mode->height);
    }
}