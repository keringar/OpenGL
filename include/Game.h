#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Renderer/StaticRenderer.h"
#include "Renderer/TextRenderer.h"
#include "Renderer/Camera.h"

class Game {
public:
    Game(Window& window, StaticRenderer& renderer, Camera& camera);
    ~Game();

    void update(double deltaTime);
    void render();

private:
    Window& m_window;
    StaticRenderer& m_terrainRenderer;
    Camera& m_camera;
    Tilemap m_tilemap;
};

#endif //GAME_H
