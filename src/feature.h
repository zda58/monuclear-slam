#ifndef FEATURE_H
#define FEATURE_H

class Feature {
public:
    Feature(int x, int y) : x(x), y(y) {};
    int get_x() { return x; };
    int get_y() { return y; };
private:
    int x;
    int y;
};

#endif