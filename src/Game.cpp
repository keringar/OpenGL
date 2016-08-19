#include "Game.h"

Game::Game(Window& window, Input& input, TileRenderer& renderer, Camera& camera) : m_window{window}, m_input{input}, m_terrainRenderer{renderer}, m_camera(camera){
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

void Game::Render(){
    m_terrainRenderer.render(m_camera.getViewMatrix(), m_camera.getProjectionMatrix());
    m_textRenderer.renderText(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "Test");

    m_window.swap();
}

void Game::HandleInput() {
    //Input queue - filled with events
    std::vector<Event> pressed_keys, held_keys;
    m_input.handle_input(held_keys, pressed_keys);

    //Send events to registered listeners
    for (const auto& event : held_keys) {
        switch(event) {
            case Event::MOVE_UP:
                m_camera.moveForward();
                break;
            case Event::MOVE_RIGHT:
                m_camera.moveRight();
                break;
            case Event::MOVE_BACK:
                m_camera.moveBack();
                break;
            case Event::MOVE_LEFT:
                m_camera.moveLeft();
                break;
            case Event::ZOOM_IN:
                m_camera.zoomIn();
                break;
            case Event::ZOOM_OUT:
                m_camera.zoomOut();
                break;
            default:
                //Do nothing
                break;
        }
    }

    for (const auto& event : pressed_keys) {
        switch(event) {
            case Event::QUIT:
                m_window.close();
                break;
            case Event::TOGGLE_FULLSCREEN:
                Log::log(std::to_string(Util::randomInt()));
                //m_window.toggleFullscreen();
                break;
            default:
                //Do nothing
                break;
        }
    }
}