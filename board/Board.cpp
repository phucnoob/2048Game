#include<iostream>
#include<vector>

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
        switch (direction)
        {
            case UP:
                data->moveUp();
                data->addRandom();
                break;
            case DOWN:
                data->moveDown();
                data->addRandom();
                break;
            case LEFT:
                data->moveLeft();
                data->addRandom();
                break;
            case RIGHT:
                data->moveRight();
                data->addRandom();
                break;        
            default:
                break;
        }
        return true;
    }

    void render(SDL_Renderer *renderer) {
        ui->updateBoardUI(data->getData());
        ui->render(renderer);
    }

    ~Board() {
        ui = NULL;
        data = NULL;
    }
};