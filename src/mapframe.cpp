#include "mapframe.h"
#include <iostream>

MapFrame::MapFrame(cv::Mat &mat) {
    this->height = mat.rows;
    this->width = mat.cols;
    this->frame_buffer = std::vector<std::array<uint8_t, 3>>(height * width, {0, 0, 0});
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            cv::Vec3b &pixel = mat.at<cv::Vec3b>(y, x);
            int idx = y * this->width + x;
            // BGR -> RGB for now
            frame_buffer[idx] = {pixel[2], pixel[1], pixel[0]};
        }
    }
};

void MapFrame::add_point(int width, int height) {
    if (height < 0 || height > this->height || width < 0 || width > this->width) {
        std::cerr << "incorrect coordinates: " << height << ", " << width << std::endl;
        return;
    }
    this->points.push_back({width, height});
};


cv::Mat MapFrame::draw_mat() {
    cv::Mat mat(this->height, this->width, CV_8UC3);

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            cv::Vec3b &pixel = mat.at<cv::Vec3b>(y, x);
            int idx = y * this->width + x;
            const auto &rgb = this->frame_buffer[idx];
            // RGB -> BGR for now
            pixel[0] = rgb[2];
            pixel[1] = rgb[1];
            pixel[2] = rgb[0];
        }
    }

    for (auto point = this->points.begin(); point != this->points.end(); point++) {
        int x = (*point)[0];
        int y = (*point)[1];

        for (int ypt = y - 1; ypt < y + 2; ypt++) {
            if (ypt < 0 || ypt > this->height) {
                continue;
            }
            for (int xpt = x - 1; xpt < x + 2; xpt++) {
                if (xpt < 0 || xpt > this->width) {
                    continue;
                }
                cv::Vec3b &pixel = mat.at<cv::Vec3b>(xpt, ypt);
                pixel[1] = 0xFF;
            }
        }
    }

    return mat;
}