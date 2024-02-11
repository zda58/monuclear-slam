#include <iostream>
#include <opencv2/opencv.hpp>
#include <SDL2/SDL.h>

#include "cvprocessor.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    std::string home_dir = getenv("HOME");
    cv::VideoCapture video(std::string(home_dir) + "/Videos/indoordrone.mp4");
    // Initialize SDL
    if (!video.isOpened()) {
        std::cerr << "Error opening video file" << std::endl;
        return {};
    }

    int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int frame_count = video.get(cv::CAP_PROP_FRAME_COUNT);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL Square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "begin process" << std::endl;
    std::vector<MapFrame> frames = process(video);
    std::cout << "end process" << std::endl;

    //auto frame_iter = frames.begin();
    // Main loop
    bool quit = false;
    SDL_Event event;
    for (auto frame_iter = frames.begin(); frame_iter != frames.end(); frame_iter++) {
        std::cout << "LOOP" << std::endl;
        // Read frame from video
        for (int i = 0; i < 100; i++) {
            int randx = rand() % width;
            int randy = rand() % height;
            frame_iter->add_point(randx, randy);
        }
        cv::Mat frame = frame_iter->draw_mat();
        int width = frame_iter->width;
        int height = frame_iter->height;
        // Check if frame is empty (end of video)
        if (frame.empty()) {
            break;
        }

        // Convert OpenCV Mat to SDL_Surface
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(frame.data, width, height, 24, 3 * width, 0x0000FF, 0x00FF00, 0xFF0000, 0);

        // Convert SDL_Surface to SDL_Texture
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        // Clear screen
        SDL_RenderClear(renderer);

        // Copy texture to renderer
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderDrawPoint(renderer, 30, 30);
        // Update screen
        SDL_RenderPresent(renderer);

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        if (quit) {
            break;
        }

        // Delay for 1 second
        SDL_Delay(1000);

        // Free texture
        SDL_DestroyTexture(texture);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}