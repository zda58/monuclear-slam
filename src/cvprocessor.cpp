#include "cvprocessor.h"
#include <opencv2/imgcodecs/legacy/constants_c.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/calib3d/calib3d_c.h>

std::vector<MapFrame> process_video_frames(cv::VideoCapture &video) {
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

void process_pose_matrices(std::vector<cv::KeyPoint> &previous_keypoints, std::vector<cv::KeyPoint> &current_keypoints, std::vector<cv::DMatch> &matches) {
    cv::Mat rotation_matrix, transformation_matrix;

    // placeholders
    double focal_x = 750.0;
    double focal_y = 750.0;
    double focal_length = 750.0;

    double principal_x = 360.0;
    double principal_y = 450.0;
    cv::Mat intrinsics = (cv::Mat_<double>(3, 3) <<
        focal_x, 0, principal_x,
        0, focal_y, principal_y,
        0, 0, 1
    );
    cv::Point2d principal_point(principal_x, principal_y);
    std::vector<cv::Point2f> query_points, train_points;

    for (auto match = matches.begin(); match != matches.end(); match++) {
        cv::Point2d query_index = previous_keypoints[match->queryIdx].pt;
        query_points.push_back(query_index);
        cv::Point2d train_index = current_keypoints[match->trainIdx].pt;
        train_points.push_back(train_index);
    }
    cv::Mat matrix_essential = cv::findEssentialMat(query_points, train_points, focal_length, principal_point);
    recoverPose(matrix_essential, query_points, train_points, rotation_matrix, transformation_matrix, focal_length, principal_point);
}