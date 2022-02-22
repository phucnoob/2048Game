#include<vector>
#include<SDL2/SDL.h>

using namespace std;

#include"Tile.h"

class BoardUI {
    public:
        SDL_Renderer *renderer = nullptr;
        SDL_Texture *font = nullptr;
    private:
        vector<vector<Tile*>> board;
        int width, height;
        int x, y;
        int size;
        int marginWidth;
        int titleWidth;
        int radio = 10;
        SDL_Rect rect;

    public: 
        BoardUI( SDL_Renderer *renderer,int size, int width) {

            this->renderer = renderer;

            this->size = size;
            this->width = width;
            //square
            this->height = width;
            this->x = x;
            this->y = y;
            this->rect = {x, y, width, width};
            // we have size tile, size + 1 margin about 1/5 tile
            this->marginWidth = width / (size + 1 + radio * size);
            this->titleWidth = radio * marginWidth;
        }

        void setPos(int x, int y) {
            this->x = x;
            this->y = y;
            this->rect = {x, y, width, width};
            this->board = initBoardTiles(size);
        }

        vector<vector<Tile*>> initBoardTiles(int size) {

            vector<vector<Tile*>> tiles(size, vector<Tile*>(size, NULL));
            int init = (width - size * titleWidth) / (size + 1);

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    tiles[i][j] = new Tile(0,0, 0);
                    // Important!!, from matrix to Oxy is transposition
                    tiles[i][j]->setPos(
                        init + (init + titleWidth) * j,
                        init + (init + titleWidth) * i
                    );
                    tiles[i][j]->offSet(x, y);
                    tiles[i][j]->setWidth(titleWidth);
                    tiles[i][j]->setColor(0, 255, 255, 255);
                }

            }

            return tiles;
        };

        void updateBoardUI(vector<vector<int>> boardData) {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    this->board[i][j]
                    ->setValue(boardData[i][j]);
                }
            }
        }

        int getWidth() {
            return width;
        }

        void setWidth(int width) {
            this->width = width;
        }

        int getHeight() {
            return height;
        }

        void setHeight(int height) {
            this->height = height;
        }

        int getSize() {
            return size;
        }

        void setSize(int size) {
            this->size = size;
        }

        void render(SDL_Renderer *renderer) {
            // #bbada0
            SDL_SetRenderDrawColor(renderer, 0xbb, 0xad, 0xa0, 0xff);
            SDL_RenderFillRect(renderer, &rect);
           
            for (size_t i = 0; i < board.size(); i++)
            {
                for (size_t j = 0; j < board.size(); j++)
                {
                    board[i][j]->render(renderer, font);
                }
            }
        }

    
};
