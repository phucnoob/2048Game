
#include "Button.h"
class MenuButton : public Button {
    public:
    int size = 0;

    MenuButton(string text,int x, int y,int size, int padding = 0) :
    Button(text, x, y, padding)
    {
        this->size = size;
    }

    MenuButton(string text,int x, int y,int size, int padX,int padY = 0) :
    Button(text, x, y, padX, padY)
    {
        this->size = size;
    }

    int listen(SDL_Event *event){
        if (Button::listen(event)) {
            return size;
        } else {
            return 0;
        }
    }
};