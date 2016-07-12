#include "Input.h"

//Define static variables
std::map<int, bool> Input::held_keys;
std::map<int, bool> Input::pressed_keys;
std::map<int, bool> Input::released_keys;

Input::Input(Window& window) : m_config{"keys"} {
    glfwSetKeyCallback(window, KeyboardCallback);

    //m_config = Configuration("keys");

    event_map.emplace(Event::QUIT, convertToKeyCode(m_config.get("quit")));
    event_map.emplace(Event::MOVE_UP, convertToKeyCode(m_config.get("move_up")));
    event_map.emplace(Event::MOVE_RIGHT, convertToKeyCode(m_config.get("move_right")));
    event_map.emplace(Event::MOVE_DOWN, convertToKeyCode(m_config.get("move_down")));
    event_map.emplace(Event::MOVE_LEFT, convertToKeyCode(m_config.get("move_left")));
}

Input::~Input() {

}

std::vector<Event> Input::handle_input() {
    glfwPollEvents();
    std::vector<Event> input_queue;

    for (const auto &pair : event_map) {
        if (was_pressed(pair.second)) {
            input_queue.push_back(pair.first);
        }
    }

    clear_keys();

    return input_queue;
}

bool Input::is_held(int key) {
    return held_keys[key];
}

bool Input::was_released(int key) {
    return released_keys[key];
}

bool Input::was_pressed(int key) {
    return pressed_keys[key];
}

void Input::clear_keys() {
    pressed_keys.clear();
    released_keys.clear();
}

void Input::KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        pressed_keys[key] = true;
        held_keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        released_keys[key] = true;
        held_keys[key] = false;
    }
}

//Make better
int Input::convertToKeyCode(std::string key) {
    if (key == "SPACE") {
        return 32;
    } else if (key == "'") {
        return 39;
    } else if (key == ",") {
        return 44;
    } else if (key == "-") {
        return 45;
    } else if (key == ".") {
        return 46;
    } else if (key == "/") {
        return 47;
    } else if (key == "0") {
        return 48;
    } else if (key == "1") {
        return 49;
    } else if (key == "2") {
        return 50;
    } else if (key == "3") {
        return 51;
    } else if (key == "4") {
        return 52;
    } else if (key == "5") {
        return 53;
    } else if (key == "6") {
        return 54;
    } else if (key == "7") {
        return 55;
    } else if (key == "8") {
        return 56;
    } else if (key == "9") {
        return 57;
    } else if (key == ";") {
        return 59;
    } else if (key == "=") {
        return 61;
    } else if (key == "A") {
        return 65;
    } else if (key == "B") {
        return 66;
    } else if (key == "C") {
        return 67;
    } else if (key == "D") {
        return 68;
    } else if (key == "E") {
        return 69;
    } else if (key == "F") {
        return 70;
    } else if (key == "G") {
        return 71;
    } else if (key == "H") {
        return 72;
    } else if (key == "I") {
        return 73;
    } else if (key == "J") {
        return 74;
    } else if (key == "K") {
        return 75;
    } else if (key == "L") {
        return 76;
    } else if (key == "M") {
        return 77;
    } else if (key == "N") {
        return 78;
    } else if (key == "O") {
        return 79;
    } else if (key == "P") {
        return 80;
    } else if (key == "Q") {
        return 81;
    } else if (key == "R") {
        return 82;
    } else if (key == "S") {
        return 83;
    } else if (key == "T") {
        return 84;
    } else if (key == "U") {
        return 85;
    } else if (key == "V") {
        return 86;
    } else if (key == "W") {
        return 87;
    } else if (key == "X") {
        return 88;
    } else if (key == "Y") {
        return 89;
    } else if (key == "Z") {
        return 90;
    } else if (key == "[") {
        return 91;
    } else if (key == "\\") {
        return 92;
    } else if (key == "]") {
        return 93;
    } else if (key == "`") {
        return 96;
    } else if (key == "WORLD_1") {
        return 161;
    } else if (key == "WORLD_2") {
        return 162;
    } else if (key == "ESCAPE") {
        return 256;
    } else if (key == "ENTER") {
        return 257;
    } else if (key == "TAB") {
        return 258;
    } else if (key == "BACKSPACE") {
        return 259;
    } else if (key == "INSERT") {
        return 260;
    } else if (key == "DELETE") {
        return 261;
    } else if (key == "RIGHT") {
        return 262;
    } else if (key == "LEFT") {
        return 263;
    } else if (key == "DOWN") {
        return 264;
    } else if (key == "UP") {
        return 265;
    } else if (key == "PAGE_UP") {
        return 266;
    } else if (key == "PAGE_DOWN") {
        return 267;
    } else if (key == "HOME") {
        return 268;
    } else if (key == "END") {
        return 269;
    } else if (key == "CAPS_LOCK") {
        return 280;
    } else if (key == "SCROLL_LOCK") {
        return 281;
    } else if (key == "NUM_LOCK") {
        return 282;
    } else if (key == "PRINT_SCREEN") {
        return 283;
    } else if (key == "PAUSE") {
        return 284;
    } else if (key == "F1") {
        return 290;
    } else if (key == "F2") {
        return 291;
    } else if (key == "F3") {
        return 292;
    } else if (key == "F4") {
        return 293;
    } else if (key == "F5") {
        return 294;
    } else if (key == "F6") {
        return 295;
    } else if (key == "F7") {
        return 296;
    } else if (key == "F8") {
        return 297;
    } else if (key == "F9") {
        return 298;
    } else if (key == "F10") {
        return 299;
    } else if (key == "F11") {
        return 300;
    } else if (key == "F12") {
        return 301;
    } else if (key == "F13") {
        return 302;
    } else if (key == "F14") {
        return 303;
    } else if (key == "F15") {
        return 304;
    } else if (key == "F16") {
        return 305;
    } else if (key == "F17") {
        return 306;
    } else if (key == "F18") {
        return 307;
    } else if (key == "F19") {
        return 308;
    } else if (key == "F20") {
        return 309;
    } else if (key == "F21") {
        return 310;
    } else if (key == "F22") {
        return 311;
    } else if (key == "F23") {
        return 312;
    } else if (key == "F24") {
        return 313;
    } else if (key == "F25") {
        return 314;
    } else if (key == "KP_0") {
        return 320;
    } else if (key == "KP_1") {
        return 321;
    } else if (key == "KP_2") {
        return 322;
    } else if (key == "KP_3") {
        return 323;
    } else if (key == "KP_4") {
        return 324;
    } else if (key == "KP_5") {
        return 325;
    } else if (key == "KP_6") {
        return 326;
    } else if (key == "KP_7") {
        return 327;
    } else if (key == "KP_8") {
        return 328;
    } else if (key == "KP_9") {
        return 329;
    } else if (key == "KP_DECIMAL") {
        return 330;
    } else if (key == "KP_DIVIDE") {
        return 331;
    } else if (key == "KP_MULTIPLY") {
        return 332;
    } else if (key == "KP_SUBTRACT") {
        return 333;
    } else if (key == "KP_ADD") {
        return 334;
    } else if (key == "KP_ENTER") {
        return 335;
    } else if (key == "KP_EQUAL") {
        return 336;
    } else if (key == "LEFT_SHIFT") {
        return 340;
    } else if (key == "LEFT_CONTROL") {
        return 341;
    } else if (key == "LEFT_ALT") {
        return 342;
    } else if (key == "LEFT_SUPER") {
        return 343;
    } else if (key == "RIGHT_SHIFT") {
        return 344;
    } else if (key == "RIGHT_CONTROL") {
        return 345;
    } else if (key == "RIGHT_ALT") {
        return 346;
    } else if (key == "RIGHT_SUPER") {
        return 347;
    } else if (key == "MENU") {
        return 348;
    } else {
        return -1;
    }
}