#include<vector>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

using namespace std;

#include"utils/SDL_Utils.h"
#include"utils/font.h"
#include"board/Board.cpp"

class Game {
    public:
    bool isRun = true;
    long frame = 0;
    int size = 4;
    const int WIDTH = 540;
    const int HEIGHT = 720;

    SDL_Color BACKGROUND = {0, 0, 0, 255};
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *font = nullptr;
    SDL_Event event;

    Board *board;

    void init() {
        initSDL(window, renderer, "Hello", WIDTH, HEIGHT);
        board = new Board(4, WIDTH, 0, HEIGHT - WIDTH);
        font = loadTexture("assets/OpenSans-Regular_0.png", renderer);
        board->init(renderer, font);
    }

    void clearScreen() {
        SDL_SetRenderDrawColor(renderer,
            BACKGROUND.r,
            BACKGROUND.g,
            BACKGROUND.b,
            BACKGROUND.a);
        SDL_RenderClear(renderer);
    }

    void listen() {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
            {
                isRun = false;
            } else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        board->move(Board::DIRECTION::LEFT);
                        break;
                    case SDLK_RIGHT:
                         board->move(Board::DIRECTION::RIGHT);
                        break;
                    case SDLK_UP:
                         board->move(Board::DIRECTION::UP);
                        break;
                    case SDLK_DOWN:
                         board->move(Board::DIRECTION::DOWN);
                        break;
                default:
                    break;
                }
            }
        }
    }

    void render() {
        clearScreen();
        board->render(renderer);
        testRenderText();
        SDL_RenderPresent(renderer);
    }

    void testRenderText() {
        
        long time = SDL_GetTicks();
        frame++;
        BitmapText *text = new BitmapText("Time passed: " + to_string(time / 1000) + " s.");
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        BitmapText *fps = new BitmapText("FPS: "+ to_string((int)(frame * 1000.0 / time)), 32);
        fps->render(renderer, font, 0, 50);
        text->render(renderer, font, 0,0);
    }
};