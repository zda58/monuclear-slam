#include "cvprocessor.h"

std::vector<MapFrame> process(cv::VideoCapture &video) {
    int frame_count = video.get(cv::CAP_PROP_FRAME_COUNT);
    std::cout << "Processing " << frame_count << " frames" << std::endl;
    std::vector<MapFrame> map_frames;
    map_frames.reserve(frame_count);
    cv::Mat frame;
    while (video.read(frame)) {
        map_frames.emplace_back(frame);
    } 
    return std::move(map_frames);
}