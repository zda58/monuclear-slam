#include "vec3.h"
#include <cmath>

Vec3::Vec3(float x, float y, float z) {
    this->e[0] = x;
    this->e[1] = y;
    this->e[2] = z;
}

float Vec3::x() {
    return this->e[0];
}

float Vec3::y() {
    return this->e[1];
}

float Vec3::z() {
    return this->e[2];
}

Vec3 Vec3::operator-() const {
    return Vec3(-e[0], -e[1], -e[2]);
}

float Vec3::operator[](int i) const {
    return e[i];
}

Vec3 Vec3::operator+=(Vec3 &v) {
    return Vec3(e[0] + v[0], e[1] + v[1], e[2] + v[2]);
}

Vec3 Vec3::operator*=(float f) {
    return Vec3(e[0] * f, e[1] * f, e[2] * f);
}

Vec3 Vec3::operator/=(float f) {
    return Vec3(e[0] / f, e[1] / f, e[2] / f);
}

float Vec3::length() {
    return sqrt(this->length_squared());
}

float Vec3::length_squared() {
    return e[0] * e[0] + e[1] * e[1] + e[2] + e[2];
}