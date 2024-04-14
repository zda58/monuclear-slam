#ifndef CVPROCESSOR_H
#define CVPROCESSOR_H

#include <vector>
#include "mapframe.h"

std::vector<MapFrame> process(cv::VideoCapture &video);

#endif