#include <Util.h>
#include "Tilemap.h"

Tilemap::Tilemap() {
    m_tilemapHeight = 0;
    m_tilemapWidth = 0;
}

Tilemap::Tilemap(int width, int height, int seed) {
    m_tilemapHeight = height;
    m_tilemapWidth = width;

    //m_noise = FastNoise(seed);
}

Tilemap::~Tilemap() {

}

const int Tilemap::getWidth() {
    return m_tilemapWidth;
}

const int Tilemap::getHeight() {
    return m_tilemapHeight;
}

const int Tilemap::getTileID(int x, int y) {
    return 0;
}

void Tilemap::setTile(int x, int y, int tileID) {

}