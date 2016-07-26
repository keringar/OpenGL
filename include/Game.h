#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Input.h"
#include "Renderer/TileRenderer.h"
#include "Renderer/Camera.h"

class Game {
public:
    Game(Window& window, Input& input, TileRenderer& renderer, Camera& camera);

    ~Game();

    bool isRunning();

    void HandleInput();

    void Update(double deltaTime);

    void Render();

private:
    Window& m_window;
    Input& m_input;
    TileRenderer& m_renderer;
    Camera& m_camera;
};

#endif //GAME_H
