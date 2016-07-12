#include "Game.h"

Game::Game(Window& window, Input& input, Renderer& renderer) : m_window(window), m_input(input), m_renderer(renderer) {
    //Get input, renderer, audio, window
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
                glfwSetWindowSize(m_window, 640, 480);
                break;
        }
    }
}

void Game::Update() {
    //Call update on all game objects
}

void Game::Render() {
    std::vector<Renderable> render_queue();
    m_renderer.submit(render_queue);
    m_renderer.issueRenderCommands();
}