#ifndef OPENGL_TILEMAP_H
#define OPENGL_TILEMAP_H

#include "FastNoise.h"

class Tilemap {
    public:
        Tilemap(int width, int height, int seed);
        ~Tilemap();

        const int getWidth();
        const int getHeight();
        const int getTileID(int x, int y);

    private:
        FastNoise m_noise;

        int m_tilemapWidth, m_tilemapHeight;
};

#endif //OPENGL_TILEMAP_H