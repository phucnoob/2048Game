#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

#include "utils/SDL_Utils.h"
#include "utils/font.h"
#include "utils/Button.h"
#include "utils/MenuButton.h"
#include "board/Board.cpp"

enum GameState
{
    MENU,
    RUN,
    END
};

enum GameType
{
    EASY = 4,
    MEDIUM = 5,
    HARD = 6
};

class Game
{
public:
    bool isRun = true;
    bool isGameOver = false;
    GameState state = MENU;
    long frame = 0;
    int size = 3;
    size_t score = 0;
    const int WIDTH = 540;
    const int HEIGHT = 720;

    Uint32 lastTicks = 0;

    SDL_Color BACKGROUND = {45, 52, 54, 255};
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *font = nullptr;
    SDL_Event event;
    // Game screen
    BitmapText *scoreTxt = nullptr;
    BitmapText *fps = nullptr;
    Button *undoBtn = nullptr;

    Board *board;

    // GameOver screen
    BitmapText *finalScoreTxt = nullptr;
    BitmapText *message = nullptr;
    Button *newGameBtn = nullptr;
    Button *quitBtn = nullptr;

    // Menu screen
    BitmapText *welcome = nullptr;
    vector<MenuButton *> gameTypes = {
        new MenuButton("3x3", 0, 0, 3, 64, 16),
        new MenuButton("4x4", 0, 0, 4, 64, 16),
        new MenuButton("5x5", 0, 0, 5, 64, 16)};

    void init()
    {
        initSDL(window, renderer, "2048 Game", WIDTH, HEIGHT);
        board = new Board(size, WIDTH, 0, HEIGHT - WIDTH);
        font = loadTexture("assets/OpenSans-Regular_0.png", renderer);
        board->init(renderer, font);

        // colors
        gameTypes[0]->setColor(231, 76, 60);
        gameTypes[1]->setColor(230, 126, 34);
        gameTypes[2]->setColor(241, 196, 15);
    }

    void clearScreen()
    {
        SDL_SetRenderDrawColor(renderer,
                               BACKGROUND.r,
                               BACKGROUND.g,
                               BACKGROUND.b,
                               BACKGROUND.a);
        SDL_RenderClear(renderer);
    }

    void restartGame()
    {
        board = new Board(size, WIDTH, 0, HEIGHT - WIDTH);
        board->init(renderer, font);

    }

    void listen()
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRun = false;
            }
            if (state == GameState::END)
            {
                if (newGameBtn->listen(&event))
                {
                    state = GameState::MENU;
                    board = nullptr;
                    return;
                } else if(quitBtn->listen(&event)) {
                    isRun = false;
                    return;
                }
            }
            else if (state == GameState::RUN)
            {
                board->listen(&event);
            }
            else if (state == GameState::MENU)
            {
                for (MenuButton *option : gameTypes)
                {
                    int size = option->listen(&event);
                    if (size != 0)
                    {
                        this->size = size;
                        state = GameState::RUN;
                        restartGame();
                        return;
                    }
                }
            }
        }
    }

    void render()
    {
        clearScreen();
        if (state == GameState::RUN)
        {
            isGameOver = false;
            renderGame();
        }
        else if (state == GameState::MENU)
        {
            isGameOver = false;
            renderMenu();
        }
        else if (state == GameState::END)
        {
            renderEnd();
        }
        frame++;
        SDL_RenderPresent(renderer);
    }

    void renderMenu()
    {
        welcome = new BitmapText("Select board size:");

        welcome->render(renderer, font, 
            (WIDTH - welcome->block.w) / 2,
            64
        );

        int initPos = -100;
        for (MenuButton *option : gameTypes)
        {
            option->setPos(
                (WIDTH - option->bounds.w) / 2,
                (HEIGHT - option->bounds.h) / 2 + initPos);
            // option->
            option->render(renderer, font);
            initPos += 100;
        }
    }

    void renderGame()
    {
        board->render(renderer);
        renderScore();
        renderFPS();
    }

    void renderEnd()
    {
        message = new BitmapText("Game Over!!");
        scoreTxt = new BitmapText("Your score: " + to_string(score));

        newGameBtn = new Button("New Game", 0, 0, 12);
        quitBtn = new Button("Quit", 0,0, 62, 12);
        // cout << newGameBtn->bounds.w << " ,"<< newGameBtn->bounds.w << endl;
        newGameBtn->setColor(9, 132, 227);

        message->render(renderer, font,
                        (WIDTH - message->block.w) / 2,
                        (HEIGHT - message->block.h) / 2 - 100);
        newGameBtn->setPos(
            (WIDTH - newGameBtn->bounds.w) / 2,
            (HEIGHT - newGameBtn->bounds.h) / 2);
        newGameBtn->render(renderer, font);

        quitBtn->setColor(231, 76, 70);
        quitBtn->setPos(
            (WIDTH - quitBtn->bounds.w) / 2,
            (HEIGHT - quitBtn->bounds.h) / 2 + 64);

        quitBtn->render(renderer, font);
        scoreTxt->render(renderer, font,
                         (WIDTH - scoreTxt->block.w) / 2,
                         (HEIGHT - scoreTxt->block.h) / 2 + 240);
        // cout << newGameBtn->bounds.w << " ,"<< newGameBtn->bounds.w << endl;
    }

    void renderScore()
    {
        score = board->getScore();
        scoreTxt = new BitmapText("Score: " + to_string(score));
        scoreTxt->render(renderer, font, 16, 16);
    }

    void renderFPS()
    {
        // if 1 seconds has passed, we update lastick
        if (lastTicks < SDL_GetTicks() - 1000)
        {
            lastTicks = SDL_GetTicks();
            // update ui
            fps = new BitmapText("FPS: " + to_string(frame));
            // reset frame
            frame = 0;
        }
        fps->render(renderer, font, WIDTH - fps->block.w - 16, 16);
        // cout << fps->block.x << "," << fps->block.y << "," << fps->block.w << "," << fps->block.h << endl;
    }
    void handleGameOver()
    {

        if (board == nullptr)
            return;

        if (board->isGameEnded())
        {
            isGameOver = true;
            state = GameState::END;
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