#include <Util.h>
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

//Constructor
Renderer::Renderer(const Window& window) : m_window{window} {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //Create texture manager, shader manager and model manager
}

//Deconstructor
Renderer::~Renderer() {

    //Destroy texture, shader and model managers
}

//Copy constructor
Renderer::Renderer(const Renderer& render) : m_window{render.m_window} {

}

//Load all textures, models
bool Renderer::loadAll() {
    return true;
}

//Get render queue
void Renderer::submit(std::vector<Renderable>& render_queue) {
    for(const auto& item : render_queue){
        GLuint VAO, VBO;
    }
}

//Issue gpu commands
void Renderer::issueRenderCommands() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    Shader program;

    program.compile(vertexShader, fragmentShader);
    program.use();

    program.SetFloat("time", sin(glfwGetTime() * 4) + 0.2);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    m_window.swap();
}

