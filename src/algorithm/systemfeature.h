#ifndef SYSTEMFEATURE_H
#define SYSTEMFEATURE_H

#include "vec3.h"

class SystemFeature {
public:

private:
    Vec3 origin;
    float azimuth;
    float elevation;
    float inverse_depth; // reciprocal of point depth 
};

#endif