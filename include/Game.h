#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Renderer/TileRenderer.h"
#include "Renderer/TextRenderer.h"
#include "Renderer/Camera.h"

class Game {
public:
    Game(Window& window, TileRenderer& renderer, Camera& camera);

    ~Game();

    bool isRunning();

    void HandleInput(Event& event);

    void Update(double deltaTime);

    void Render();

private:
    Window& m_window;
    TileRenderer& m_terrainRenderer;
    Camera& m_camera;

    TextRenderer m_textRenderer;
    Tilemap m_tilemap;
};

#endif //GAME_H
