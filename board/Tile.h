#include<SDL2/SDL.h>
#include<string>
SDL_Color fg1 = {255, 255, 255, 255};


#include"../utils/font.h"
class Tile
{   public:
        static SDL_Color *Colors;
    private:
        /* data */
        SDL_Color color;
        int value;
        SDL_Rect block;
        BitmapText *text;
    public:
        int getX() {
            return block.x;
        }
        int getY() {
            return block.y;
        }

        int getValue() {
            return value;
        }

        void setValue(int value) {
            this->value = value;

            this->text = new BitmapText(to_string(value));
        }

        void setPos(int x, int y) {
            this->block.x = x;
            this->block.y = y;
        }

        void setWidth(int width) {
            //square
            this->block.w = width;
            this->block.h = width;
        }

        Tile(int x, int y, int value) {
            this->block.x = x;
            this->block.y = y;
            this->value = value;
            this->text = new BitmapText(to_string(this->value), 48);
        }

        void offSet(int x, int y) {
            setPos(this->getX() + x, this->getY() + y);
        }

        void setColor(int r, int g, int b, int a) {
            this->color.r = r;
            this->color.g = g;
            this->color.b = b;
            this->color.a = a;
        }

        int resovleColor() {
            int _v = this->value;
            int count = 0;
            while(_v > 1) {
                count++;
                _v /= 2;
            }
            if(count <= 11) {
                this->color = Colors[count];
            } else {
                this->color = {10, 61, 98, 255};
            }
            return count;
        }

        void render(SDL_Renderer *renderer, SDL_Texture *font) {

            resovleColor();
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &block);            
            if(value == 0) {
                return;
            }
            //foreground
            int fg = 0;
            if (value > 256)
            {
                fg = 255;
            } else {
                fg = value * 64;
            }
            

            SDL_SetTextureColorMod(font, fg, fg, fg);
            text->render(renderer, font,
                block.x + (block.w - text->block.w) / 2,
                block.y + (block.h - text->block.h) / 2);

            //reset color
            SDL_SetTextureColorMod(font, 255, 255, 255);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }
};

SDL_Color color0 = {238, 228, 218, 90};
SDL_Color color1 = {238, 228, 218, 255};
SDL_Color color2 = {238, 225, 201, 255};
SDL_Color color3 = {243, 178, 122, 255};
SDL_Color color4 = {246, 150, 100, 255};
SDL_Color color5 = {247, 124, 95, 255};
SDL_Color color6 = {247, 95, 59, 255};
SDL_Color color7 = {238, 228, 100, 255};
SDL_Color color8 = {237, 204, 98, 255};
SDL_Color color9 = {250, 152, 58, 255};
SDL_Color color10 = {229, 80, 57, 255};
SDL_Color color11 = {74, 105, 189, 255};
static SDL_Color colors[] = {
    color0,
    color1,
    color2,
    color3,
    color4,
    color5,
    color6,
    color7,
    color8,
    color9,
    color10,
    color11
};

SDL_Color* Tile::Colors = colors;
