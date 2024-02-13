#ifndef VEC3_H
#define VEC3_H

class Vec3 {
public:
    Vec3();
    Vec3(float x, float y, float z);
    float x();
    float y();
    float z();

    Vec3 operator-() const;
    float operator[](int i) const;

    Vec3 operator+=(Vec3 &v);
    Vec3 operator*=(float f);
    Vec3 operator/=(float f);
    float length();
    float length_squared();
private:
    float e[3];
};


#endif