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
    long frame = 60;
    int size = 6;
    size_t score = 0;
    const int WIDTH = 540;
    const int HEIGHT = 720;

    Uint32 lastTicks = 0;

    SDL_Color BACKGROUND = {149, 165, 166, 255};
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *font = nullptr;
    BitmapText *scoreTxt = nullptr;
    BitmapText *message = nullptr;
    BitmapText *fps = nullptr;
    SDL_Event event;

    Board *board;

    void init() {
        initSDL(window, renderer, "Hello", WIDTH, HEIGHT);
        board = new Board(size, WIDTH, 0, HEIGHT - WIDTH);
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
        // testRenderText();
        renderScore();
        renderFPS();
        SDL_RenderPresent(renderer);
        frame++;
    }

    void renderScore() {
        score = board->getScore();
        scoreTxt = new BitmapText("Score: " + to_string(score));
        scoreTxt->render(renderer, font, 16,16);
    }

    void renderFPS() {
        // if 1 seconds has passed, we update lastick
        if (lastTicks < SDL_GetTicks() - 1000) {
            lastTicks = SDL_GetTicks();
            // update ui
            fps = new BitmapText("FPS: " + to_string(frame));
            // reset frame
            frame = 0;
        }
        fps->render(renderer, font, WIDTH - fps->block.w - 16 ,16);
        // cout << fps->block.x << "," << fps->block.y << "," << fps->block.w << "," << fps->block.h << endl;
    }
    void handleGameOver() {
        if (board->isGameEnded())
        {
            cout << score;
            isRun = false;
        }
    }
    // void testRenderText() {
        
    //     long time = SDL_GetTicks();
        
    //     BitmapText *text = new BitmapText("Time passed: " + to_string(time / 1000) + " s.");
    //     SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    //     BitmapText *fps = new BitmapText("FPS: "+ to_string((int)(frame * 1000.0 / time)), 32);
    //     fps->render(renderer, font, 0, 50);
    //     text->render(renderer, font, 0,0);
    // }
};