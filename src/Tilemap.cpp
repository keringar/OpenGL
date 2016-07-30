#include <Util.h>
#include "Tilemap.h"

Tilemap::Tilemap(int width, int height, int seed) {
    m_tilemapHeight = height;
    m_tilemapWidth = width;

    m_noise = FastNoise(seed);
}

Tilemap::~Tilemap(){

}

const int Tilemap::getWidth() {
    return m_tilemapWidth;
}

const int Tilemap::getHeight() {
    return m_tilemapHeight;
}

const int Tilemap::getTileID(int x, int y){
    float noise = 100 * m_noise.GetSimplex(x, y);

    if(noise < 20){
        return 64;
    } else {
        return 0;
    }
}