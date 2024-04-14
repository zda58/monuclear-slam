#ifndef LENSVIEW_H
#define LENSVIEW_H
#include <SDL2/SDL.h>
#include <opencv2/opencv.hpp>

class LensView {
public:
    LensView(int width, int height);
    void clean();
    void render(cv::Mat &mat);
private:
    int width, height;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

#endif