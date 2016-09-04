#ifndef INPUT_H
#define INPUT_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "EventDispatcher.h"
#include "Util.h"

class Window;

class Input {
public:
    Input(const Window& window, EventDispatcher& dispatcher);

    void update();

    void setKey(std::string key, EventType type);
    void clearKeys();

    static void KeyboardCallback(GLFWwindow *window, int key, int scancode, int actions, int mods);
    static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

private:
    bool is_held(int key);
    bool was_released(int key);
    bool was_pressed(int key);

    int convertToKeyCode(std::string key);

    std::map<int, EventType> m_keyMap;

    Configuration m_config;
    EventDispatcher& m_dispatcher;

    static std::map<int, bool> held_keys;
    static std::map<int, bool> pressed_keys;
};

#endif //INPUT_H
