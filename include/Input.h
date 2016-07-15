#ifndef INPUT_H
#define INPUT_H

#include <Window.h>
#include <vector>
#include <GLFW/glfw3.h>

enum class Event {
    QUIT,
    MOVE_UP,
    MOVE_RIGHT,
    MOVE_BACK,
    MOVE_LEFT,
    TOGGLE_FULLSCREEN
};

class Input {
public:
    Input(GLFWwindow* window);

    ~Input();

    std::vector<Event> handle_input();

    static void KeyboardCallback(GLFWwindow *window, int key, int scancode, int actions, int mods);

private:
    bool is_held(int key);

    bool was_released(int key);

    bool was_pressed(int key);

    void clear_keys();

    int convertToKeyCode(std::string key);

    Configuration m_config;

    std::map<Event, int> event_map;

    static std::map<int, bool> held_keys;
    static std::map<int, bool> pressed_keys;
    static std::map<int, bool> released_keys;
};

#endif //INPUT_H
