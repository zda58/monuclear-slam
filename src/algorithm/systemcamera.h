#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "quaternion.h"

class SystemCamera {
public:

private:
    Vec3 coordinates;
    Quaternion orientation;
    Vec3 linear_velocity;
    Vec3 angular_velocity;
};

#endif