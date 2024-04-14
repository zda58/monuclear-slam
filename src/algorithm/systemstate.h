#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <vector>
#include "systemcamera.h"
#include "systemfeature.h"

class SystemState {
public:

private:
    SystemCamera camera;
    std::vector<SystemFeature> features;
};

#endif