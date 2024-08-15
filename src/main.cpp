#include <iostream>
#include <globals.h>
#include "Core/Game.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Game game;
    game.Create("Dinkler", SCREEN_WIDTH, SCREEN_HEIGHT);
    while(game.Running) {
        game.Update();
    }
    return 0;
}
