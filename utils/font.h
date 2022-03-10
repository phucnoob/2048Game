#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

typedef struct
{
    char a;
    int x, y;
    int width, height;
    int xoffset, yoffset;
    int xadvance;
} glyph;

glyph glyphs[] = {
    {32, 0, 0, 0, 0, 0, 0, 8},
    {33, 248, 29, 4, 24, 2, 11, 8},
    {34, 59, 72, 9, 9, 2, 11, 13},
    {35, 46, 24, 19, 24, 1, 11, 21},
    {36, 100, 74, 15, 27, 2, 10, 19},
    {37, 0, 81, 24, 24, 2, 11, 27},
    {38, 24, 81, 22, 24, 2, 11, 24},
    {39, 73, 72, 3, 9, 2, 11, 7},
    {40, 228, 0, 8, 29, 1, 11, 9},
    {41, 236, 0, 8, 29, 1, 11, 10},
    {42, 212, 15, 16, 15, 1, 10, 18},
    {43, 211, 35, 15, 16, 2, 15, 19},
    {44, 68, 72, 5, 8, 1, 31, 8},
    {45, 28, 75, 8, 3, 1, 24, 10},
    {46, 36, 75, 4, 4, 2, 31, 8},
    {47, 176, 24, 12, 24, 0, 11, 12},
    {48, 123, 0, 15, 24, 2, 11, 18},
    {49, 229, 48, 9, 24, 3, 11, 18},
    {50, 132, 48, 15, 24, 2, 11, 18},
    {51, 133, 24, 15, 24, 1, 11, 18},
    {52, 83, 76, 17, 24, 1, 11, 18},
    {53, 138, 0, 15, 24, 2, 11, 18},
    {54, 130, 97, 15, 24, 2, 11, 18},
    {55, 145, 72, 15, 24, 1, 11, 18},
    {56, 147, 48, 15, 24, 2, 11, 18},
    {57, 148, 24, 15, 24, 2, 11, 18},
    {58, 217, 89, 4, 18, 2, 17, 8},
    {59, 223, 69, 6, 22, 0, 17, 8},
    {60, 195, 72, 15, 17, 2, 15, 19},
    {61, 44, 72, 15, 9, 2, 19, 19},
    {62, 197, 18, 15, 17, 2, 15, 19},
    {63, 162, 48, 13, 24, 0, 11, 14},
    {64, 0, 24, 25, 27, 2, 11, 29},
    {65, 25, 24, 21, 24, 0, 11, 20},
    {66, 116, 48, 16, 24, 3, 11, 20},
    {67, 65, 24, 18, 24, 2, 11, 20},
    {68, 70, 0, 18, 24, 3, 11, 23},
    {69, 163, 24, 13, 24, 3, 11, 17},
    {70, 168, 0, 13, 24, 3, 11, 16},
    {71, 51, 0, 19, 24, 2, 11, 23},
    {72, 99, 50, 17, 24, 3, 11, 23},
    {73, 248, 53, 3, 24, 3, 11, 9},
    {74, 188, 24, 9, 30, -3, 11, 9},
    {75, 100, 24, 17, 24, 3, 11, 20},
    {76, 175, 48, 13, 24, 3, 11, 17},
    {77, 21, 51, 23, 24, 3, 11, 29},
    {78, 65, 81, 18, 24, 3, 11, 24},
    {79, 30, 0, 21, 24, 2, 11, 25},
    {80, 153, 0, 15, 24, 3, 11, 19},
    {81, 0, 51, 21, 30, 2, 11, 25},
    {82, 106, 0, 17, 24, 3, 11, 20},
    {83, 145, 96, 15, 24, 1, 11, 18},
    {84, 83, 100, 17, 24, 1, 11, 19},
    {85, 88, 0, 18, 24, 3, 11, 24},
    {86, 44, 48, 20, 24, 0, 11, 19},
    {87, 0, 0, 30, 24, 0, 11, 30},
    {88, 46, 81, 19, 24, 0, 11, 18},
    {89, 64, 48, 19, 24, 0, 11, 18},
    {90, 117, 24, 16, 24, 1, 11, 18},
    {91, 210, 89, 7, 29, 3, 11, 11},
    {92, 181, 0, 12, 24, 0, 11, 12},
    {93, 244, 0, 8, 29, 0, 11, 10},
    {94, 208, 0, 17, 15, 1, 11, 18},
    {95, 15, 123, 14, 3, 0, 37, 14},
    {96, 21, 75, 7, 6, 1, 9, 9},
    {97, 197, 35, 14, 18, 1, 17, 17},
    {98, 115, 100, 15, 25, 3, 10, 20},
    {99, 210, 71, 13, 18, 2, 17, 15},
    {100, 130, 72, 15, 25, 2, 10, 20},
    {101, 188, 54, 15, 18, 2, 17, 18},
    {102, 174, 101, 12, 26, 1, 9, 12},
    {103, 83, 50, 16, 26, 1, 17, 18},
    {104, 160, 72, 14, 25, 3, 10, 20},
    {105, 251, 58, 3, 24, 3, 11, 8},
    {106, 202, 89, 8, 32, -2, 11, 8},
    {107, 160, 97, 14, 25, 3, 10, 17},
    {108, 252, 33, 3, 25, 3, 10, 8},
    {109, 0, 105, 25, 18, 3, 17, 30},
    {110, 203, 53, 14, 18, 3, 17, 20},
    {111, 67, 105, 16, 18, 2, 17, 19},
    {112, 100, 101, 15, 26, 3, 17, 20},
    {113, 115, 74, 15, 26, 2, 17, 20},
    {114, 238, 51, 10, 18, 3, 17, 13},
    {115, 217, 51, 12, 18, 2, 17, 15},
    {116, 238, 29, 10, 22, 1, 13, 12},
    {117, 193, 0, 15, 18, 3, 17, 20},
    {118, 186, 101, 16, 18, 0, 17, 16},
    {119, 25, 105, 25, 18, 0, 17, 25},
    {120, 50, 105, 17, 18, 0, 17, 17},
    {121, 83, 24, 17, 26, -1, 17, 16},
    {122, 226, 30, 12, 18, 1, 17, 14},
    {123, 185, 72, 10, 29, 1, 11, 12},
    {124, 252, 0, 3, 33, 8, 10, 18},
    {125, 174, 72, 11, 29, 1, 11, 12},
    {126, 0, 123, 15, 5, 2, 20, 19}};

glyph resolveChar(char c)
{
    return glyphs[c - 32];
}

int scaleNumber(int number, float scale) {
    return (int)(scale * number);
}

void resovleString(string s, vector<SDL_Rect>& rects, vector<SDL_Rect>& pos, float scale = 1)
{
    vector<glyph> result(s.length());
    vector<SDL_Rect> pos_tmp(s.length());

    for (size_t i = 0; i < s.length(); i++)
    {
        result[i] = resolveChar(s[i]);
        if (i == 0)
        {
            pos_tmp[i] = {  
                    scaleNumber(result[i].xoffset, scale),
                    result[i].yoffset,
                    scaleNumber(result[i].width, scale),
                    scaleNumber(result[i].height, scale)
                };
        } else {
            pos_tmp[i] = { 
                            result[i].xoffset + pos_tmp[i-1].x + scaleNumber(result[i-1].xadvance, scale),
                            result[i].yoffset ,
                            scaleNumber(result[i].width, scale),
                            scaleNumber(result[i].height, scale)
                        };
        }

        
    }

    for (size_t i = 0; i < result.size(); i++)
    {
        rects.push_back({result[i].x,result[i].y, result[i].width, result[i].height });
    }
    

    pos = vector<SDL_Rect>(pos_tmp);
}

class BitmapText
{
public:

private:
    vector<SDL_Rect> rects;
    vector<SDL_Rect> pos;
public:
    SDL_Rect block;
    BitmapText(string text)
    {
        resovleString(text, rects, pos);
        block.w = pos[pos.size() - 1].x + pos[pos.size() - 1].w;
        block.h = pos[pos.size() - 1].y + pos[pos.size() - 1].h;
    }
    BitmapText(string text, int fontSize)
    {
        float scale = fontSize / 16.0f;
        resovleString(text, rects, pos, scale);
    }

    void setPos(int x, int y) {
        block.x = x;
        block.y = y;
    }

    void render(SDL_Renderer *renderer,SDL_Texture *font, int x, int y)
    {
        for (size_t i = 0; i < rects.size(); i++)
        {
            pos[i].x += x;
            pos[i].y += y;
            SDL_RenderCopy(renderer, font, &rects[i] ,&pos[i]);
        // reset pos forrender many times
            pos[i].x -= x;
            pos[i].y -= y;
        }
        

    }
};
