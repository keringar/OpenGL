#ifndef OPENGL_TILEMAP_H
#define OPENGL_TILEMAP_H

class Tilemap {
    public:
        Tilemap(int width, int height);
        ~Tilemap();

        const int getWidth();
        const int getHeight();
        const int getTileID(int x, int y);

    private:
        int m_tilemapWidth, m_tilemapHeight;
};

#endif //OPENGL_TILEMAP_H