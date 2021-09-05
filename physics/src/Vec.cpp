#include "Vec.h"

Vec operator+(const Vec& x, const Vec& y) {
    return Vec(x.x + y.x, x.y + y.y);
}

Vec operator*(const double& c, const Vec& y) {
    return Vec(c * y.x, c * y.y);

}

Vec operator-(const Vec& x, const Vec& y) {
    return Vec(x.x - y.x, x.y - y.y);
}

double dot(const Vec& x, const Vec& y){ 
    return (x.x * y.x) + (x.y * y.y); 
}

double magnitude(const Vec& x) {
    return sqrt((x.x * x.x) + (x.y * x.y));
}

Vec operator/(const Vec& y, const double& x) {
    if (x != 0) {
        return Vec(y.x / x, y.y / x);
    }
    return y;
}