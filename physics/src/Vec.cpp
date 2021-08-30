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