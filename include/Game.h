#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"

class Game {
public:
    Game(Window& window, Input& input, Renderer& renderer, Camera& camera);

    ~Game();

    bool isRunning();

    void HandleInput();

    void Update();

    void Render();

private:
    Window m_window;
    Input m_input;
    Renderer m_renderer;
    Camera m_camera;
};

#endif //GAME_H
