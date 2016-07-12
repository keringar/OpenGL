#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Input.h"
#include <memory>

class Game {
public:
    Game(Window &window, Input &input);

    ~Game();

    bool isRunning();

    void HandleInput();

    void Update();

    void Render();

private:
    Window m_window;
    Input m_input;

};

#endif //GAME_H
