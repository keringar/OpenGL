#include "Game.h"

Game::Game(Window& window, Input& input, Renderer& renderer, Camera& camera) : m_window{window}, m_input{input}, m_renderer{renderer}, m_camera(camera){

}

Game::~Game() {

}

bool Game::isRunning() {
    return m_window.isOpen();
}

void Game::HandleInput() {
    //Input queue - filled with events
    std::vector<Event> input_queue = m_input.handle_input();

    //Send events to registered listeners
    for (const auto& event : input_queue) {
        switch(event) {
            case Event::QUIT:
                m_window.close();
                break;
            case Event::MOVE_UP:

                break;
            case Event::MOVE_RIGHT:

                break;
            case Event::MOVE_DOWN:

                break;
            case Event::MOVE_LEFT:

                break;
        }
    }
}

void Game::Update() {
    //Call update on all game objects
}

void Game::Render() {
    m_renderer.submit();
    m_renderer.issueRenderCommands(m_camera.getViewMatrix());
}