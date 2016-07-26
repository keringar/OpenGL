#include "Game.h"

Game::Game(Window& window, Input& input, TileRenderer& renderer, Camera& camera) : m_window{window}, m_input{input}, m_renderer{renderer}, m_camera(camera){

}

Game::~Game() {

}

bool Game::isRunning() {
    return m_window.isOpen();
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
                m_window.toggleFullscreen();
                break;
            default:
                //Do nothing
                break;
        }
    }
}

void Game::Update(double deltaTime) {
    //Call update on all game objects
    m_camera.update(deltaTime);
}

void Game::Render() {
    m_renderer.issueRenderCommands(m_camera.getViewMatrix());
}