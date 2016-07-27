#include "Tilemap.h"

Tilemap::Tilemap(int width, int height) {
    m_tilemapHeight = height;
    m_tilemapWidth = width;
}

Tilemap::~Tilemap(){

}

const int Tilemap::getWidth() {
    return m_tilemapWidth;
}

const int Tilemap::getHeight() {
    return m_tilemapHeight;
}

const unsigned int Tilemap::getTileID(int x, int y){
    return 0;
}
