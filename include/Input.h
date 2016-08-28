#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <GLFW/glfw3.h>

#include "Util.h"
#include "EventDispatcher.h"

class Input {
public:
    Input(GLFWwindow* window, EventDispatcher& dispatcher);

    void update();

    void setKey(std::string key, EventType type);

    static void KeyboardCallback(GLFWwindow *window, int key, int scancode, int actions, int mods);
    static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

private:
    GLFWwindow* m_window;

    bool is_held(int key);
    bool was_released(int key);
    bool was_pressed(int key);

    void clear_keys();
    int convertToKeyCode(std::string key);

    std::map<int, EventType> keyMap;

    Configuration m_config;
    EventDispatcher& m_dispatcher;

    static std::map<int, bool> held_keys;
    static std::map<int, bool> pressed_keys;
};

#endif //INPUT_H
