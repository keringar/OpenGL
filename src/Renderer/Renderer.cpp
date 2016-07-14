#include <Util.h>
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

//Constructor
Renderer::Renderer(const Window& window) : m_window{window} {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); //Sky-Blue

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
void Renderer::submit() {

}

//Issue gpu commands
void Renderer::issueRenderCommands(glm::mat4 view) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const int rows = 16;
    const int cols = 16;

    //Vertices
    std::vector<GLfloat> vertices;
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            vertices.push_back((c - 8) / (GLfloat)(rows));
            vertices.push_back((r - 8) / (GLfloat)(cols));
            vertices.push_back((GLfloat) 0);
        }
    }

    //Indices
    std::vector<GLuint> indices;
    for(GLuint r = 0; r < rows - 1; ++r){
        indices.push_back(r * cols);
        for(int c = 0; c < cols; ++c){
            indices.push_back(r * cols + c);
            indices.push_back((r + 1) * cols + c);
        }
        indices.push_back((r + 1) * cols + (cols - 1));
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    std::string vertexShader = File::readFile("shaders/basic.vert");
    std::string fragmentShader = File::readFile("shaders/basic.frag");

    Shader program;

    program.compile(vertexShader, fragmentShader);
    program.use();

    glm::mat4 model;
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    program.SetMatrix4("mvp", m_window.getProjectionMatrix(90.0f) * view * model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    m_window.swap();
}

