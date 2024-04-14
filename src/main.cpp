#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <SDL2/SDL.h>

#include <opencv2/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/legacy/constants_c.h>

#include "mapframe.h"
#include "cvprocessor.h"
#include "mapview.h"
#include "lensview.h"

cv::VideoCapture get_video(int argc, char **argv);

int main(int argc, char **argv) {
    cv::VideoCapture video = get_video(argc, argv);
    int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int frame_count = video.get(cv::CAP_PROP_FRAME_COUNT);
    
    std::cout << "Video resolution: " << width << " by " << height << std::endl;
    std::vector<MapFrame> frames = process(video);
    std::cout << "Finished processing " << frame_count << " frames" << std::endl;

    MapView map(1200, 800);
    LensView lens(width, height);

    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
    bool quit = false;
    SDL_Event event;

    bool init = true;
    for (auto frame_iter = frames.begin(); frame_iter != frames.end(); frame_iter++) {
        frame_iter->detect_features();
        if (!init) {
            // Match features, estimate motion, draw to map
        }

        cv::Mat frame = frame_iter->draw_mat();
        if (frame.empty()) {
            std::cerr << "empty frame detected" << std::endl;
            exit(1);
        }
        lens.render(frame);
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
        init = false;
    }

    map.clean();
    lens.clean();
    SDL_Quit();

    return 0;
}

cv::VideoCapture get_video(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Supply an absolute or relative path to an mp4 file" << std::endl;
        exit(1);
    }
    
    std::string video_path = std::string(argv[1]);
    
    if (video_path.size() < 4 || video_path.compare(video_path.size() - 4, 4, ".mp4")) {
        std::cout << "invalid mp4 path" << std::endl;
        exit(1);
    }

    cv::VideoCapture video(video_path);
    if (!video.isOpened()) {
        std::cerr << "Error opening video file" << std::endl;
        exit(1);
    }

    return std::move(video);
}