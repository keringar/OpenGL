#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Input.h"
#include "Renderer/Renderer.h"

class Game {
public:
    Game(Window& window, Input& input, Renderer& renderer);

    ~Game();

    bool isRunning();

    void HandleInput();

    void Update();

    void Render();

private:
    Window m_window;
    Input m_input;
    Renderer m_renderer;

};

#endif //GAME_H
