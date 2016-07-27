#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <vector>
#include <Window.h>
#include <Tilemap.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture2D.h>
#include <glm/detail/type_mat4x4.hpp>

class TileRenderer{
    public:
        TileRenderer(const Window& m_window);
        ~TileRenderer();

        //Copy constructor
        TileRenderer(const TileRenderer& render);

        bool loadAll();
        void loadTileMap(Tilemap& tilemap);
        void render(glm::mat4 view, glm::mat4 perspective);

    private:
        const Window& m_window;

        Shader m_shader;
        Texture2D m_texture;

        GLuint VAO;
        GLuint VBO[2]; //Stores vertices and tex coords in separate buffers

        int tileMapWidth = 0;
        int tileMapHeight = 0;
};

#endif