#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>
#include "feature.h"

class MapFrame {
public:
    MapFrame(cv::Mat &mat);
    std::vector<std::array<uint8_t, 3>> &get_frame_buffer() { return frame_buffer; };
    cv::Mat draw_mat();
    void detect_features();
    int height;
    int width;
private:
    std::vector<std::array<uint8_t, 3>> frame_buffer;
    std::vector<Feature> features;
};

#endif
