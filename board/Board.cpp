#include<iostream>
#include<vector>
#include<functional>

typedef void (*callback_function)(string);

#include"BoardData.h"
#include"BoardUI.h"

class Board {
    
    BoardUI *ui;
    BoardData *data;
    SDL_Renderer *renderer;

    public:
    enum DIRECTION {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    Board(int size, int width, int x, int y) {
        ui = new BoardUI(this->renderer ,size, width);
        ui->setPos(x, y);
        data = new BoardData(size);
    }

    void init(SDL_Renderer *renderer, SDL_Texture *font) {
        this->renderer = renderer;
        this->ui->font = font;
    }

    bool move(DIRECTION direction) {
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

    void render(SDL_Renderer *renderer) {
        ui->updateBoardUI(data->getData());
        ui->render(renderer);
    }

    bool isGameEnded() {
        return data->isGameEnded();
    }

    size_t getScore() {
        return data->getScore();
    }

    ~Board() {
        ui = NULL;
        data = NULL;
    }
};