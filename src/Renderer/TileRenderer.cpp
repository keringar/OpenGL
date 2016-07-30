#include <Util.h>
#include "Renderer/TileRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

//Constructor
TileRenderer::TileRenderer(const Window& window) : m_window{window} {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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

    m_texture.load("data/textureAtlas.png");

    return true;
}

void TileRenderer::loadTileMap(Tilemap& tilemap){
    tileMapHeight = tilemap.getHeight();
    tileMapWidth = tilemap.getWidth();
    int textureAtlasWidth = m_texture.Width;
    int textureAtlasHeight = m_texture.Height;

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
    //Texture atlas is 8x8 with 64x64 size tiles
    std::vector<GLfloat> texCoords;
    for(int i = 0; i < tileMapHeight; ++i){
        for(int j = 0; j < tileMapWidth; ++j){
            //X and Y are for the top left corner of the tile
            int ID = tilemap.getTileID(j, i);

            GLfloat x = 64.0f * (ID % (m_texture.Width / 64));
            GLfloat y = 64.0f * (ID / (m_texture.Height / 64));

            //Bottom-left corner
            texCoords.push_back((x + 0.5f) / textureAtlasWidth);  // X
            texCoords.push_back((y + 63.5f) / textureAtlasHeight);  // Y
            //Bottom-right corner
            texCoords.push_back((x + 63.5f) / textureAtlasWidth);
            texCoords.push_back((y + 63.5f) / textureAtlasHeight);
            //Top-left corner
            texCoords.push_back((x + 0.5f) / textureAtlasWidth);
            texCoords.push_back((y + 0.5f) / textureAtlasHeight);

            //Top-left corner
            texCoords.push_back((x + 0.5f) / textureAtlasWidth);
            texCoords.push_back((y + 0.5f) / textureAtlasHeight);
            //Bottom-right corner
            texCoords.push_back((x + 63.5f) / textureAtlasWidth);
            texCoords.push_back((y + 63.5f) / textureAtlasHeight);
            //Top-right corner
            texCoords.push_back((x + 63.5f) / textureAtlasWidth);
            texCoords.push_back((y + 0.5f) / textureAtlasHeight);
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
    m_shader.SetMatrix4("mvp", perspective * view * model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6 * tileMapHeight * tileMapWidth);
    glBindVertexArray(0);
}