#include <Util.h>
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

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
    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    std::string vertexShader = File::readFile("shaders/basic.vert");
    std::string fragmentShader = File::readFile("shaders/basic.frag");

    Log::log(vertexShader);
    Log::log(fragmentShader);

    Shader program;

    program.compile(vertexShader, fragmentShader);
    program.use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    m_window.swap();
}

