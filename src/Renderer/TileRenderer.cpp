#include <Util.h>
#include "Renderer/TileRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

//Constructor
TileRenderer::TileRenderer(const Window& window) : m_window{window} {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_MULTISAMPLE);
}

//Deconstructor
TileRenderer::~TileRenderer() {
    //Destroy texture, shader and model managers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

//Copy constructor
TileRenderer::TileRenderer(const TileRenderer& render) : m_window{render.m_window} {

}

//Load all textures, models
bool TileRenderer::loadAll() {
    //Try to load all resources
    std::string vertexShader = File::readString("data/shaders/basic.vert");
    std::string fragmentShader = File::readString("data/shaders/basic.frag");
    m_shader.compile(vertexShader, fragmentShader);

    //Generate tile map
    for(int r = 0; r < TileMap.size(); ++r) {
        for (int c = 0; c < TileMap[r].size(); ++c) {
            TileMap[r][c] = 0;
        }
    }

    //Generate vertices
    std::vector<GLfloat> vertices;
    for(int i = 0; i <= tileMapHeight; ++i){
        for(int j = 0; j <= tileMapWidth; ++j){
            //Bottom-left corner
            vertices.push_back(j);      // X
            vertices.push_back(i);      // Y
            vertices.push_back(0.0f);   // Z
        }
    }

    //Generate indices
    std::vector<GLuint> indices;
    for(GLuint i = 0; i < tileMapHeight; ++i){
        for(GLuint j = 0; j < tileMapWidth; ++j){
            GLuint verticesWidth = tileMapWidth + 1;

            indices.push_back(((i + 1) * verticesWidth) + j);
            indices.push_back((i * verticesWidth) + j);
            indices.push_back((i * verticesWidth) + j + 1);

            indices.push_back(((i + 1) * verticesWidth) + j);
            indices.push_back((i * verticesWidth) + j + 1);
            indices.push_back(((i + 1) * verticesWidth + j + 1));
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

//Issue gpu commands
void TileRenderer::issueRenderCommands(glm::mat4 view) {
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader.use();

    glm::mat4 model;
    m_shader.SetMatrix4("mvp", m_window.getProjectionMatrix() * view * model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6 * tileMapHeight * tileMapWidth, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    m_window.swap();
}

