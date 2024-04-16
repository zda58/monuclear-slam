#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>

class MapFrame {
public:
    MapFrame(cv::Mat &mat);
    cv::Mat draw_mat();
    std::vector<cv::KeyPoint> &get_keypoints() { return this->keypoints; };
    cv::Mat &get_descriptors() { return this->descriptors; };
    void detect_features();
    int height;
    int width;
private:
    cv::Mat frame;
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
};

#endif
