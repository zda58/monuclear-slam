#ifndef CVPROCESSOR_H
#define CVPROCESSOR_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "mapframe.h"

std::vector<MapFrame> process(cv::VideoCapture &video); 


#endif