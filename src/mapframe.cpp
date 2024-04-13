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

void MapFrame::detect_features() {
    int x = 0;
    int y = 0;
    this->features.push_back( Feature(x, y) );
}

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

    for (auto point = this->features.begin(); point != this->features.end(); point++) {
        int x = (*point).get_x();
        int y = (*point).get_y();

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