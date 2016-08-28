#include "Tilemap.h"
#include <vector>

Tilemap::Tilemap() {
    m_tilemapHeight = 0;
    m_tilemapWidth = 0;
}

Tilemap::Tilemap(int width, int height, int seed) {
    m_tilemapHeight = height;
    m_tilemapWidth = width;
}

Tilemap::~Tilemap() {

}

const int Tilemap::getWidth() const {
    return m_tilemapWidth;
}

const int Tilemap::getHeight() const {
    return m_tilemapHeight;
}

const int Tilemap::getTileID(int x, int y) const {
    return 5;
}

void Tilemap::setTile(int x, int y, int tileID) {

}

void Tilemap::generateMesh() {
    GLuint textureAtlasWidth = 448;//m_texture.Width;
    GLuint textureAtlasHeight = 448;//m_texture.Height;

    //Generate vertices
    std::vector<GLfloat> vertices;
    for(int i = 0; i < m_tilemapHeight; ++i){
        for(int j = 0; j < m_tilemapHeight; ++j){
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
    for(int i = 0; i < m_tilemapHeight; ++i){
        for(int j = 0; j < m_tilemapHeight; ++j){
            //X and Y are for the top left corner of the tile
            int ID = getTileID(j, i);

            GLfloat x = 64.0f * (ID % (448 / 64));
            GLfloat y = 64.0f * (ID / (448 / 64));

            //Bottom-left corner
            texCoords.push_back((x + 0.5f) / textureAtlasWidth);   // X
            texCoords.push_back((y + 63.5f) / textureAtlasHeight); // Y
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

    //Bind VAO
    glBindVertexArray(VAO);

    //Send vertex buffer data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Send tex coord data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    //Unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

const GLuint Tilemap::getMesh() const {
    return VAO;
}