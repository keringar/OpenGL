#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <vector>
#include <Window.h>
#include <Tilemap.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture2D.h>
#include <glm/detail/type_mat4x4.hpp>

class StaticRenderer{
    public:
        StaticRenderer(const Window& m_window);
        ~StaticRenderer();

        //Copy constructor
        StaticRenderer(const StaticRenderer& render);

        bool loadAll();
        void render(glm::mat4 view, glm::mat4 perspective, const Tilemap& map);

    private:
        const Window& m_window;

        Shader m_shader;
        Texture2D m_texture;
};

#endif