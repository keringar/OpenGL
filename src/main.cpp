#include <Game.h>

int main() {
    //Initialize window
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


    //Initialize input
    Input input(window);

    //Pass window, renderer, audio and input to game
    Game game(window, input, renderer, camera);

    //Delta time
    const double timeDelta = 20.0 / 1000.0; // 20 update ticks per second
    double timeAccumulator = 0;
    double startTime = 0;

    //Game Loop
    while (game.isRunning()) {
        double currentTimeSimulated = 0;
        startTime = glfwGetTime();

        while(timeAccumulator >= timeDelta){
            game.Update(timeDelta);
            timeAccumulator -= timeDelta;
            currentTimeSimulated += timeDelta;
        }

        game.Render();
        game.HandleInput();

        timeAccumulator += glfwGetTime() - startTime;

        //Log::log(std::to_string(1 / (glfwGetTime() - startTime)));
    }

    return 0;
}