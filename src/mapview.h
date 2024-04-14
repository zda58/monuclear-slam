#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <SDL2/SDL_video.h>

class MapView {
public:
    MapView(int width, int height);
    ~MapView();
private:
    int width, height;
    SDL_Window *window = nullptr;
    SDL_GLContext context = nullptr;
};


#endif