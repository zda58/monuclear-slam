#include <iostream>
#include "mapview.h"

MapView::MapView(int width, int height) {
    this->width = width;
    this->height = height;
    this->window = SDL_CreateWindow("Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_OPENGL);
    if (this->window == nullptr) {
        std::cerr << "Failed to create map window: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->context = SDL_GL_CreateContext(this->window);
    if (this->context == NULL) {
        std::cerr << "Failed to create map window context: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void MapView::clean() {
    SDL_DestroyWindow(this->window);
    SDL_GL_DeleteContext(this->context);
}