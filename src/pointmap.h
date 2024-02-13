#ifndef POINTMAP_H
#define POINTMAP_H

#include <vector>
#include "vec3.h"

class PointMap {
public:
    PointMap(Vec3 camera_origin, Vec3 direction);
    void add_map_point(Vec3 point);
    void add_movement_point(Vec3 point);
private:
    std::vector<Vec3> map_points;
    std::vector<Vec3> movement_points;
    std::vector<Vec3> locations;
    Vec3 camera_origin;
    Vec3 direction;
};



#endif