#ifndef POINTMAP_H
#define POINTMAP_H

#include <vector>
#include "vec3.h"

class PointMap {
public:
    PointMap();
    void add_point();
private:
    std::vector<Vec3> points;
    std::vector<Vec3> locations;
    Vec3 origin;
    Vec3 direction;
};



#endif