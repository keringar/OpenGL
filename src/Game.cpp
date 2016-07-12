#include "Game.h"

Game::Game(Window &window, Input &input) : m_window(window), m_input(input) {
    //Init input, renderer, audio, window
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
    for (const auto &event : input_queue) {
        if (event == Event::QUIT) {
            m_window.close();
        }
    }
}

void Game::Update() {
    //Call update on all game objects
}

void Game::Render() {
    //Get list of renderable objects
    //Sort
    //Render with respective renderers
}