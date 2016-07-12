#include <Game.h>

int main() {
    //Initialize Window
    Window window;
    if (!window.init()) {
        return -1;
    }

    //Initialize renderer
    Renderer renderer(window);
    if(!renderer.loadAll()){
        return -1;
    }

    //Initialize audio


    //Initialize input
    Input input(window);

    //Pass window, renderer, audio and input to game
    Game game(window, input, renderer);

    //Game Loop
    while (game.isRunning()) {
        game.HandleInput();
        game.Update();
        game.Render();
    }

    return 0;
}