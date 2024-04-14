#include <iostream>
#include <opencv2/opencv.hpp>
#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "mapframe.h"
#include "cvprocessor.h"
#include <opencv2/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/legacy/constants_c.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Supply an absolute or relative path to an mp4 file" << std::endl;
        return 1;
    }
    
    std::string video_path = std::string(argv[1]);
    
    if (video_path.size() < 4 || video_path.compare(video_path.size() - 4, 4, ".mp4")) {
        std::cout << "invalid mp4 path" << std::endl;
        return 1;
    }

    cv::VideoCapture video(video_path);
    if (!video.isOpened()) {
        std::cerr << "Error opening video file" << std::endl;
        return 1;
    }

    int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int frame_count = video.get(cv::CAP_PROP_FRAME_COUNT);
    
    std::cout << "Video resolution: " << width << " by " << height << std::endl;
    std::vector<MapFrame> frames = process(video);
    std::cout << "Finished processing " << frame_count << " frames" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *map_window = nullptr; 
    SDL_Renderer *map_renderer = nullptr;
    SDL_Window *video_window = nullptr;
    SDL_Renderer *video_renderer = nullptr;

    map_window = SDL_CreateWindow("SDL Square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (map_window == nullptr) {
        std::cerr << "window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    map_renderer = SDL_CreateRenderer(map_window, -1, SDL_RENDERER_ACCELERATED);
    if (map_renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    video_window = SDL_CreateWindow("SDL Square", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (video_window == nullptr) {
        std::cerr << "window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    video_renderer = SDL_CreateRenderer(video_window, -1, SDL_RENDERER_ACCELERATED);
    if (video_renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
    bool quit = false;
    SDL_Event event;

    for (auto frame_iter = frames.begin(); frame_iter != frames.end(); frame_iter++) {
        frame_iter->detect_features();
        cv::Mat frame = frame_iter->draw_mat();

        int width = frame_iter->width;
        int height = frame_iter->height;
        if (frame.empty()) {
            std::cerr << "empty frame detected" << std::endl;
            return 1;
        }

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(frame.data, width, height, 24, 3 * width, 0x0000FF, 0x00FF00, 0xFF0000, 0);

        SDL_Texture *texture = SDL_CreateTextureFromSurface(video_renderer, surface);
        SDL_FreeSurface(surface);

        SDL_RenderClear(video_renderer);
        SDL_RenderCopy(video_renderer, texture, NULL, NULL);
        SDL_RenderPresent(video_renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    quit = true;
                }
            }
        }
        if (quit) {
            break;
        }

        usleep(500000);

        SDL_DestroyTexture(texture);
    }

    SDL_DestroyRenderer(video_renderer);
    SDL_DestroyWindow(video_window);
    SDL_Quit();

    return 0;
}