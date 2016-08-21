#include "Game.h"

Game::Game(Window &window, TileRenderer &renderer, Camera &camera) : m_window{window}, m_terrainRenderer{renderer},
                                                                     m_camera(camera) {
    m_tilemap = Tilemap(200, 160, Util::randomInt());
    m_camera.setLimits(0, 0, m_tilemap.getHeight(), m_tilemap.getWidth());
    m_camera.setPosition(glm::vec3(m_tilemap.getWidth() / 2, m_tilemap.getHeight() / 2, 50.0f));
    m_terrainRenderer.loadTileMap(m_tilemap);
}

Game::~Game() {

}

bool Game::isRunning() {
    return m_window.isOpen();
}

void Game::Update(double deltaTime) {
    //Call update on all game objects
    m_camera.update(deltaTime);
}

void Game::Render() {
    m_terrainRenderer.render(m_camera.getViewMatrix(), m_camera.getProjectionMatrix());
    m_textRenderer.renderText(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "Test");
}

void Game::HandleInput(Event &event) {
    switch (event.type) {
        case Event::GAME:
            switch (event.game.type) {
                case Event::GameType::MOVE_DOWN:
                    m_camera.moveBack();
                    break;
                case Event::GameType::MOVE_UP:
                    m_camera.moveForward();
                    break;
                case Event::GameType::MOVE_LEFT:
                    m_camera.moveLeft();
                    break;
                case Event::GameType::MOVE_RIGHT:
                    m_camera.moveRight();
                    break;
                case Event::GameType::ZOOM_IN:
                    m_camera.zoomIn();
                    break;
                case Event::GameType::ZOOM_OUT:
                    m_camera.zoomOut();
                    break;
            }
        case Event::MOUSE:


        default:
            break;
    }
}