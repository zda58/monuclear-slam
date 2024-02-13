#include "pointmap.h"

PointMap::PointMap(Vec3 camera_origin, Vec3 direction) {
    this->camera_origin = camera_origin;
    this->direction = direction;
}

void PointMap::add_map_point(Vec3 point) {
    this->map_points.push_back(point);
}

void PointMap::add_movement_point(Vec3 point) {
    this->movement_points.push_back(point);
}