#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "Window.h"
#include "Shader.h"
#include "Texture2D.h"

class TextRenderer {
    public:
        TextRenderer();
        ~TextRenderer();

        //Does not require view/projection matrix because is screen space
        void renderText(glm::vec2 position, glm::vec2 scale, std::string text);

    private:
        Shader m_textShader;
        Texture2D m_glyphs;
};

#endif //TEXTRENDERER_H
