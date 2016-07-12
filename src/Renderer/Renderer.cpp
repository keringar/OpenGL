#include <Util.h>
#include "Renderer/Renderer.h"

//Constructor
Renderer::Renderer(const Window& window) : m_window{window} {
    Log::log("Constructing Renderer", Log::Channels::None);
    //Create texture manager, shader manager and model manager
}

//Deconstructor
Renderer::~Renderer() {
    Log::log("Deconstructing Renderer", Log::Channels::None);
    //Destroy texture, shader and model managers
}

//Copy constructor
Renderer::Renderer(const Renderer& render) : m_window{render.m_window} {
    Log::log("Copying Renderer", Log::Channels::None);
}

//Load all textures, models
bool Renderer::loadAll() {
    Log::log("Loading textures and models", Log::Channels::None);
    return true;
}

//Get render queue
void Renderer::submit(std::vector<Renderable>& render_queue) {

}

//Issue gpu commands
void Renderer::issueRenderCommands() {
/*    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  */
}

