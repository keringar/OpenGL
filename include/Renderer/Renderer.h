#ifndef RENDERER_H
#define RENDERER_H
#include "Renderable.h"
#include <vector>
#include <Window.h>

class Renderer{
    public:
    Renderer(const Window& m_window);
        ~Renderer();

        //Copy constructor
        Renderer(const Renderer& render);

        bool loadAll();
        void submit(std::vector<Renderable>& render_queue);
        void issueRenderCommands();

    private:
        std::vector<Renderable> m_render_queue;
    const Window& m_window;
};

#endif