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

void LensView::render(cv::Mat &mat) {
    cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(mat.data, this->width, this->height, 24, 3 * width, 0x0000FF, 0x00FF00, 0xFF0000, 0);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(this->renderer, nullptr);
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
    SDL_DestroyTexture(texture);
}

void LensView::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}