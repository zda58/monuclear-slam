#include "mapframe.h"
#include <iostream>

MapFrame::MapFrame(cv::Mat &mat) {
    this->height = mat.rows;
    this->width = mat.cols;
    this->frame = mat.clone();
};

void MapFrame::detect_features() {
    cv::Ptr<cv::FeatureDetector> feature_detector = cv::ORB::create();
    feature_detector->detect(this->frame, this->keypoints);
    cv::Ptr<cv::DescriptorExtractor> descriptor_detector = cv::ORB::create();
    descriptor_detector->compute(this->frame, this->keypoints, this->descriptors);
}

cv::Mat MapFrame::draw_mat() {
    int square_thickness = 3;
    cv::Mat mat = this->frame.clone();

    for (auto point = this->keypoints.begin(); point != this->keypoints.end(); point++) {
        int x = static_cast<int>(point->pt.x);
        int y = static_cast<int>(point->pt.y);

        for (int ypt = y - 2; ypt <= y + 2; ypt++) {
            if (ypt < 0 || ypt > this->height) {
                continue;
            }
            for (int xpt = x - 2; xpt <= x + 2; xpt++) {
                if (xpt < 0 || xpt > this->width) {
                    continue;
                }
                cv::Vec3b &pixel = mat.at<cv::Vec3b>(ypt, xpt);
                pixel[1] = 0xFF;
            }
        }
    }

    return mat;
}