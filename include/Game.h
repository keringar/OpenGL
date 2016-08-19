#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Input.h"
#include "Renderer/TileRenderer.h"
#include "Renderer/TextRenderer.h"
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
    TileRenderer& m_terrainRenderer;
    Camera& m_camera;

    TextRenderer m_textRenderer;
    Tilemap m_tilemap;
};

#endif //GAME_H
