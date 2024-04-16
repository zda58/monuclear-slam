#ifndef CVPROCESSOR_H
#define CVPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "mapframe.h"

std::vector<MapFrame> process_video_frames(cv::VideoCapture &video);

void process_pose_matrices(std::vector<cv::KeyPoint> &previous_keypoints, std::vector<cv::KeyPoint> &current_keypoints, std::vector<cv::DMatch> &matches);

#endif