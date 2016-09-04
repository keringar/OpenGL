#ifndef OPENGL_TILEMAP_H
#define OPENGL_TILEMAP_H

#include <glad/glad.h>
#include "Util.h"

class Tilemap {
    public:
        Tilemap(int width, int height, int seed);
        Tilemap(const Tilemap& other) : VAO{other.VAO}, VBO{other.VBO[0], other.VBO[1]}, m_tilemapWidth{other.m_tilemapWidth}, m_tilemapHeight{other.m_tilemapHeight}, m_seed{other.m_seed} { }

        const int getWidth() const;
        const int getHeight() const;
        const int getTileID(int x, int y) const;
        void setTile(int x, int y, int tileID);

        void generateMesh();
        const GLuint getMesh() const;

    private:
        GLuint VAO;
        GLuint VBO[2];

        int m_tilemapWidth, m_tilemapHeight, m_seed;
};

#endif //OPENGL_TILEMAP_H