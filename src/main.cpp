#include <Game.h>

int main() {
    //Initialize window
    Window window;
    if (!window.init()) {
        Log::log("Window failure, quitting");
        return -1;
    }

    //Initialize renderer
    Renderer renderer(window);
    if(!renderer.loadAll()){
        Log::log("Could not load resources");
        return -1;
    }

    //Initalize camera
    Camera camera;

    //Initialize audio


    //Initialize input
    Input input(window);

    //Pass window, renderer, audio and input to game
    Game game(window, input, renderer, camera);

    //Game Loop
    while (game.isRunning()) {
        game.HandleInput();
        game.Update();
        game.Render();
    }

    return 0;
}