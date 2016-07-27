#include <Util.h>
#include "Renderer/TileRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

//Constructor
TileRenderer::TileRenderer(const Window& window) : m_window{window} {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //glEnable(GL_MULTISAMPLE);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
}

//Deconstructor
TileRenderer::~TileRenderer() {
    //Destroy texture, shader and model managers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
}

//Copy constructor
TileRenderer::TileRenderer(const TileRenderer& render) : m_window{render.m_window} {

}

//Load all textures, models
bool TileRenderer::loadAll(){
    //Try to load all resources
    std::string vertexShader = File::readString("data/shaders/TerrainShader.vert");
    std::string fragmentShader = File::readString("data/shaders/TerrainShader.frag");
    m_shader.compile(vertexShader, fragmentShader);

    m_texture.load("data/texture.jpg");

    return true;
}

void TileRenderer::loadTileMap(Tilemap& tilemap){
    tileMapHeight = tilemap.getHeight();
    tileMapWidth = tilemap.getWidth();

    //Generate vertices
    std::vector<GLfloat> vertices;
    for(int i = 0; i < tileMapHeight; ++i){
        for(int j = 0; j < tileMapWidth; ++j){
            //Bottom-left corner
            vertices.push_back(j);  // X
            vertices.push_back(i);  // Y
            //Bottom-right corner
            vertices.push_back(j + 1);
            vertices.push_back(i);
            //Top-left corner
            vertices.push_back(j);
            vertices.push_back(i + 1);

            //Top-left corner
            vertices.push_back(j);
            vertices.push_back(i + 1);
            //Bottom-right corner
            vertices.push_back(j + 1);
            vertices.push_back(i);
            //Top-right corner
            vertices.push_back(j + 1);
            vertices.push_back(i + 1);
        }
    }

    //Generate texture coords
    std::vector<GLfloat> texCoords;
    for(int i = 0; i < tileMapHeight; ++i){
        for(int j = 0; j < tileMapWidth; ++j){
            //Bottom-left corner
            texCoords.push_back(j / (GLfloat)tileMapWidth);  // X
            texCoords.push_back(i / (GLfloat)tileMapHeight);  // Y
            //Bottom-right corner
            texCoords.push_back((j + 1) / (GLfloat)tileMapWidth);
            texCoords.push_back(i / (GLfloat)tileMapHeight);
            //Top-left corner
            texCoords.push_back(j / (GLfloat)tileMapWidth);
            texCoords.push_back((i + 1) / (GLfloat)tileMapHeight);

            //Top-left corner
            texCoords.push_back(j / (GLfloat)tileMapWidth);
            texCoords.push_back((i + 1) / (GLfloat)tileMapHeight);
            //Bottom-right corner
            texCoords.push_back((j + 1) / (GLfloat)tileMapWidth);
            texCoords.push_back(i / (GLfloat)tileMapHeight);
            //Top-right corner
            texCoords.push_back((j + 1) / (GLfloat)tileMapWidth);
            texCoords.push_back((i + 1) / (GLfloat)tileMapHeight);
        }
    }

    //Submit everything to gpu
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO);

    //Send vertex buffer data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Set tex coord data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    //Unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//Issue gpu commands
void TileRenderer::render(glm::mat4 view, glm::mat4 perspective) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.use();
    m_texture.bind();

    glm::mat4 model;
    model = glm::scale(model, glm::vec3(70.0f / tileMapHeight, 70.0f / tileMapWidth, 1.0f));
    m_shader.SetMatrix4("mvp", perspective * view * model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6 * tileMapHeight * tileMapWidth);
    glBindVertexArray(0);
}