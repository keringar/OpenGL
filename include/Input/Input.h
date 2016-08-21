#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <glfw/glfw3.h>

#include "Util.h"
#include "Input/Event.h"

class Input {
public:
    Input(GLFWwindow* window);

    void update();

    std::vector<Event> eventQueue;

    void bindKey(std::string key, Event::EventType type);
    void bindKey(std::string key, Event::GameType eventType);
    void unbindKey(std::string key);

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
    std::map<int, Event> keyMap;

    Configuration m_config;

    static Event::MouseMoveEvent mouse_state;
    static std::map<int, bool> held_keys;
    static std::map<int, bool> pressed_keys;
};

#endif //INPUT_H
