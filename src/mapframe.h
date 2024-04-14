#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>
#include "feature.h"

class MapFrame {
public:
    MapFrame(cv::Mat &mat);
    cv::Mat draw_mat();
    void detect_features();
    int height;
    int width;
private:
    cv::Mat frame;
    std::vector<cv::KeyPoint> keypoints;
};

#endif
