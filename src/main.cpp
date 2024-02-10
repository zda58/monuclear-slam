#include <iostream>
#include <opencv2/opencv.hpp>
#include <SDL2/SDL.h>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

     const char *homeDir = getenv("HOME");
    // Open the video file
    cv::VideoCapture video(std::string(homeDir) + "/indoordrone.mp4");
    if (!video.isOpened()) {
        std::cerr << "Error opening video file" << std::endl;
        SDL_Quit();
        return 1;
    }

    // Get video properties
    int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);

    // Create SDL window
    SDL_Window *window = SDL_CreateWindow("Video Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create SDL renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // Read frame from video
        cv::Mat frame;
        video >> frame;

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

        // Update screen
        SDL_RenderPresent(renderer);

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
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