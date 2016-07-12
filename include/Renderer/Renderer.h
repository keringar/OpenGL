#ifndef RENDERER_H
#define RENDERER_H

class Renderer{
    public:
        Renderer();
        ~Renderer();

        //Copy constructor
        Renderer(const Renderer& render);

        bool loadAll();
        void submit(std::vector<Renderable>& render_queue);
        void issueRenderCommands();

    private:
        std::vector<Renderable> m_render_queue;
};

#endif