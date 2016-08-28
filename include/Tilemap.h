#ifndef OPENGL_TILEMAP_H
#define OPENGL_TILEMAP_H

#include <glad/glad.h>

class Tilemap {
    public:
        Tilemap();
        Tilemap(int width, int height, int seed);
        ~Tilemap();

        const int getWidth() const;
        const int getHeight() const;
        const int getTileID(int x, int y) const;
        void setTile(int x, int y, int tileID);

        void generateMesh();
        const GLuint getMesh() const;

    private:
        //FastNoise m_noise;

        GLuint VAO;
        GLuint VBO[2];

        int m_tilemapWidth, m_tilemapHeight;
};

#endif //OPENGL_TILEMAP_H