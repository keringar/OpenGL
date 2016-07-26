#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <vector>
#include <Window.h>
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
        void issueRenderCommands(glm::mat4 view);

    private:
        const Window& m_window;

        Shader m_shader;

        GLuint VAO, EBO, VBO;

        constexpr static int tileMapWidth = 10;
        constexpr static int tileMapHeight = 10;
        std::array<std::array<int, tileMapWidth>, tileMapHeight> TileMap;
};

#endif