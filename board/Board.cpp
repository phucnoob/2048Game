#include <iostream>
#include <vector>
#include <functional>

typedef void (*callback_function)(string);

#include "BoardData.h"
#include "BoardUI.h"

class Board
{

    BoardUI *ui;
    BoardData *data;
    stack<vector<vector<int>>> lasts;
    stack<size_t> lastScore;
    SDL_Renderer *renderer;

public:
    enum DIRECTION
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    Board(int size, int width, int x, int y)
    {
        ui = new BoardUI(this->renderer, size, width);
        ui->setPos(x, y);
        data = new BoardData(size);
    }

    void listen(SDL_Event *event)
    {
        if ((*event).type == SDL_KEYDOWN)
        {
            switch ((*event).key.keysym.sym)
            {
            case SDLK_LEFT:
                this->move(Board::DIRECTION::LEFT);
                break;
            case SDLK_RIGHT:
                this->move(Board::DIRECTION::RIGHT);
                break;
            case SDLK_UP:
                this->move(Board::DIRECTION::UP);
                break;
            case SDLK_DOWN:
                this->move(Board::DIRECTION::DOWN);
                break;
            default:
                break;
            }
        }
    }
    void init(SDL_Renderer *renderer, SDL_Texture *font)
    {
        this->renderer = renderer;
        this->ui->font = font;
        data->addRandom();
        data->addRandom();
    }

    void saveLastState() {
        lasts.push(data->getData());
        lastScore.push(getScore());
    }

    void undo() {

        if(lasts.empty()) return;
        data->setData(lasts.top());
        data->setScore(lastScore.top());
        lastScore.pop();
        lasts.pop();
    }

    bool move(DIRECTION direction)
    {
        // Save last board
        saveLastState();

        bool success = true;
        switch (direction)
        {
        case UP:
            success = data->moveUp();
            data->addRandom();
            break;
        case DOWN:
            success = data->moveDown();
            data->addRandom();
            break;
        case LEFT:
            success = data->moveLeft();
            data->addRandom();
            break;
        case RIGHT:
            success = data->moveRight();
            data->addRandom();
            break;
        default:
            break;
        }
        

        return success;
    }

    void render(SDL_Renderer *renderer)
    {
        ui->updateBoardUI(data->getData());
        ui->render(renderer);
    }

    bool isGameEnded()
    {
        return data->isGameEnded();
    }

    void reset(int size)
    {
        data = new BoardData(size);
    }

    size_t getScore()
    {
        return data->getScore();
    }

    void setScore(size_t score) {
        data->setScore(score);
    }

    ~Board()
    {
        ui = NULL;
        data = NULL;
    }
};