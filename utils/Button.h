#include<string>
#include"font.h"

class Button {
    BitmapText *ui;
    int padding;
    SDL_Color bg;

    public:
        SDL_Rect bounds;
        Button(string text,int x, int y, int padding = 0) {
            ui = new BitmapText(text);
            this->padding = padding;
            bounds = {
                x,
                y,
                ui->block.w + this->padding * 2,
                ui->block.h + this->padding * 2
            };
            this->padding = padding;
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
                ui->block.w + this->padding * 2,
                ui->block.h + this->padding * 2
            };
        }


        void render(SDL_Renderer *renderer,SDL_Texture *font) {
            
            SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, 255);
            SDL_RenderFillRect(renderer, &bounds);
            // y offsetfix
            ui->render(renderer, font, bounds.x + padding - 4, bounds.y + padding - 4);
        }

        bool listen(SDL_Event *event) {
            if ((*event).button.button == SDL_BUTTON_LEFT) {
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