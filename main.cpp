#include<iostream>
#include<vector>
using namespace std;

#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"Game.cpp"
/**
 * TODO
 * - new game screen
 * - undo
 * - gameover screen
 * */
int main() {
    Game *game = new Game();

    game->init();

    while(game->isRun) {
        game->listen();
        game->render();
        game->handleGameOver();
        printFPS();
    }

    return 0;
}