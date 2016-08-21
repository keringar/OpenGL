#include <Game.h>

int main() {
    //Initialize window, includes input
    Window window;
    if (!window.init()) {
        Log::log("Window failure, quitting");
        return -1;
    }

    //Initalize camera
    Camera camera(window);

    //Initialize renderer
    TileRenderer renderer(window);
    if(!renderer.loadAll()){
        Log::log("Could not load resources");
        return -1;
    }

    //Initialize audio


    //Pass dependencies to game
    Game game(window, renderer, camera);

    //Delta time
    const double timeDelta = 20.0 / 1000.0; // 20 update ticks per second
    double timeAccumulator = 0;
    double startTime = 0;

    //Game Loop
    while (window.isOpen()) {
        double currentTimeSimulated = 0;
        startTime = glfwGetTime();

        window.pollEvents();
        Event event;
        while(window.getEvent(event)) {
            if(event.type == Event::CLOSE && !event.repeat) {
                window.close();
            } else if(event.type == Event::TOGGLE_FULLSCREEN && !event.repeat) {
                window.toggleFullscreen();
            } else {
                game.HandleInput(event);
            }
        }

        while(timeAccumulator >= timeDelta){
            game.Update(timeDelta);
            timeAccumulator -= timeDelta;
            currentTimeSimulated += timeDelta;
        }

        game.Render();
        window.swap();

        timeAccumulator += glfwGetTime() - startTime;
    }

    return 0;
}