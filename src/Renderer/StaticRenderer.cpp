#include <Util.h>
#include "Renderer/StaticRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

//Constructor
StaticRenderer::StaticRenderer(const Window& window) : m_window{window}, m_shader{}, m_texture{} {

}

//Deconstructor
StaticRenderer::~StaticRenderer() {
    //Destroy texture, shader and model managers

}

//Copy constructor
StaticRenderer::StaticRenderer(const StaticRenderer& render) : m_window{render.m_window}, m_shader{}, m_texture{} {

}

//Load all textures, models
bool StaticRenderer::loadAll(){
    //Try to load all resources
    std::string vertexShader = File::readString("data/shaders/TerrainShader.vert");
    std::string fragmentShader = File::readString("data/shaders/TerrainShader.frag");
    m_shader.compile(vertexShader, fragmentShader);

    m_texture.load("data/textureAtlas.png");

    return true;
}

//Issue gpu commands
void StaticRenderer::render(glm::mat4 view, glm::mat4 perspective, const Tilemap& map) {
    m_shader.use();
    m_texture.bind();

    glm::mat4 model;
    m_shader.SetMatrix4("mvp", perspective * view * model);

    glBindVertexArray(map.getMesh());
    glDrawArrays(GL_TRIANGLES, 0, 6 * map.getHeight() * map.getWidth());
    glBindVertexArray(0);
}