#ifndef RENDERER_H
#define RENDERER_H
#include <vector>
#include <Window.h>
#include <glm/detail/type_mat4x4.hpp>

class Renderer{
    public:
    Renderer(const Window& m_window);
        ~Renderer();

        //Copy constructor
        Renderer(const Renderer& render);

        bool loadAll();
        void submit();
        void issueRenderCommands(glm::mat4 view);

    private:

        const Window& m_window;
};

#endif