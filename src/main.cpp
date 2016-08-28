#include "Window.h"
#include "Input.h"
#include "Game.h"

int main() {
    //Handles event callbacks
    EventDispatcher dispatcher;

    //Camera loads before window because it needs the window bounds
    Camera camera(dispatcher);

    //Platform specific
    Window window(dispatcher);
    if(!window.init()){
        return -1;
    }

    //Translates OS events to game events
    Input input(window, dispatcher);

    //Renderer
    StaticRenderer tileRenderer(window);
    if(!tileRenderer.loadAll()){
        Log::log("Filed to load resources");
        return -1;
    }

    //Game
    Game game(window, tileRenderer, camera);

    //Delta time
    const double timeDelta = 20.0 / 1000.0; // 20 update ticks per second
    double timeAccumulator = 0;
    double startTime = 0;

    //Game Loop
    while (window.isOpen()) {
        double currentTimeSimulated = 0;
        startTime = glfwGetTime();

        input.update();

        while(timeAccumulator >= timeDelta){
            game.update(timeDelta);
            timeAccumulator -= timeDelta;
            currentTimeSimulated += timeDelta;
        }

        game.render();
        window.swap();

        timeAccumulator += glfwGetTime() - startTime;
    }

    return 0;
}