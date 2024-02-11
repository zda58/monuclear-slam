#include "cvprocessor.h"



std::vector<MapFrame> process(cv::VideoCapture &video) {

    // Open the video file

    // Get video properties
    int width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int frame_count = video.get(cv::CAP_PROP_FRAME_COUNT);
    std::vector<MapFrame> map_frames;

    map_frames.reserve(frame_count);

    cv::Mat frame;
    while (video.read(frame)) {
        map_frames.emplace_back(frame);
    } 

    return map_frames;
}