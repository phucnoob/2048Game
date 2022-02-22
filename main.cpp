#include<iostream>
#include<vector>
using namespace std;

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"Game.cpp"

int main() {
    Game *game = new Game();

    game->init();

    while(game->isRun) {
        game->listen();
        game->render();
    }
    
    return 0;
}