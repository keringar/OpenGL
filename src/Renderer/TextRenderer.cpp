#include "Renderer/TextRenderer.h"

TextRenderer::TextRenderer() {
    auto vertexShader = File::readString("data/shaders/TextShader.vert");
    auto fragmentShader = File::readString("data/shaders/TextShader.frag");
    m_textShader.compile(vertexShader, fragmentShader);

    m_glyphs.load("data/font.png");
}

TextRenderer::~TextRenderer() {

}

void TextRenderer::renderText(glm::vec2 position, glm::vec2 scale, std::string text) {
    m_textShader.use();
}