#include<string>
#include"font.h"
#pragma once
class Button {
    BitmapText *ui;
    int padx, pady;
    SDL_Color bg;

    public:
        SDL_Rect bounds;
        Button(string text,int x, int y, int padding = 0) {
            ui = new BitmapText(text);
            this->padx = padding;
            this->pady = padding;
            bounds = {
                x,
                y,
                ui->block.w + this->padx * 2,
                ui->block.h + this->pady * 2
            };
        }

        Button(string text,int x, int y, int padX,int padY) {
            ui = new BitmapText(text);
            this->padx = padX;
            this->pady = padY;
            bounds = {
                x,
                y,
                ui->block.w + padX * 2,
                ui->block.h + padY * 2
            };
        }

        void setColor(Uint8 r, Uint8 g, Uint8 b) {
            this->bg = {r,g,b};
        }
        void setPos(int x, int y) {
            bounds.x = x;
            bounds.y = y;
        }

        void setText(string text) {
            ui = new BitmapText(text);
            bounds = {
                bounds.x,
                bounds.y,
                ui->block.w + this->padx * 2,
                ui->block.h + this->pady * 2
            };
        }


        void render(SDL_Renderer *renderer,SDL_Texture *font) {
            
            SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, 128);
            SDL_RenderFillRect(renderer, &bounds);
            // y offsetfix
            ui->render(renderer, font, bounds.x + padx - 4, bounds.y + pady - 4);
        }

        bool listen(SDL_Event *event) {
            if ((*event).type ==  SDL_MOUSEBUTTONDOWN) {
                int x = (*event).button.x;
                int y = (*event).button.y;

                if( ( x > bounds.x ) && ( x < bounds.x + bounds.w ) && ( y > bounds.y ) && ( y < bounds.y + bounds.h ) )
	            {
                    return true;
	            }
            }

            return false;
        }

        void handleClick() {
            setText("clicked");
            // setPos(bounds.x + 100, bounds.y);
        }
};