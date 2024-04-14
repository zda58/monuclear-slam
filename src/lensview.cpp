#include <iostream>
#include "lensview.h"

LensView::LensView(int width, int height) {
    this->width = width;
    this->height = height;
    this->window = SDL_CreateWindow("Lens", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (this->window == nullptr) {
        std::cerr << "window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

LensView::~LensView() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}