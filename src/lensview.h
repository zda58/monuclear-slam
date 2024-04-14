#ifndef LENSVIEW_H
#define LENSVIEW_H
#include <SDL2/SDL.h>

class LensView {
public:
    LensView(int width, int height);
    ~LensView();
private:
    int width, height;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

#endif