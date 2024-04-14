#include "vec3.h"
#include <cmath>

Vec3::Vec3(float x, float y, float z) {
    this->values[0] = x;
    this->values[1] = y;
    this->values[2] = z;
}

float Vec3::x() {
    return this->values[0];
}

float Vec3::y() {
    return this->values[1];
}

float Vec3::z() {
    return this->values[2];
}

Vec3 Vec3::operator-() const {
    return Vec3(-values[0], -values[1], -values[2]);
}

float Vec3::operator[](int i) const {
    return values[i];
}

Vec3 Vec3::operator+=(Vec3 &v) {
    return Vec3(values[0] + v[0], values[1] + v[1], values[2] + v[2]);
}

Vec3 Vec3::operator*=(float f) {
    return Vec3(values[0] * f, values[1] * f, values[2] * f);
}

Vec3 Vec3::operator/=(float f) {
    return Vec3(values[0] / f, values[1] / f, values[2] / f);
}

float Vec3::length() {
    return sqrt(this->length_squared());
}

float Vec3::length_squared() {
    return values[0] * values[0] + values[1] * values[1] + values[2] + values[2];
}