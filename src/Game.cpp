#include "Game.h"

Game::Game(Window &window, StaticRenderer& renderer, Camera& camera) : m_window{window}, m_terrainRenderer{renderer}, m_camera{camera} {
    m_tilemap = Tilemap(200, 160, 12512);
    m_tilemap.generateMesh();
    m_camera.setLimits(m_tilemap.getWidth(), m_tilemap.getHeight());
    m_camera.setPosition(m_tilemap.getWidth() / 2.0f, m_tilemap.getHeight() / 2.0f); //Exact center tile
}

Game::~Game() {

}

void Game::update(double deltaTime) {
    m_camera.update(deltaTime);
}

void Game::render(){
    m_terrainRenderer.render(m_camera.getViewMatrix(), m_camera.getProjectionMatrix(), m_tilemap);
}