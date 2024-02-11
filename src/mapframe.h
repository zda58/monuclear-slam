#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>

class MapFrame {
public:
    MapFrame(cv::Mat &mat);
    void add_point(int width, int height);
    cv::Mat draw_mat();
    int height;
    int width;
private:
    std::vector<std::array<uint8_t, 3>> frame_buffer;
    std::vector<std::array<int, 2>> points;
};

#endif