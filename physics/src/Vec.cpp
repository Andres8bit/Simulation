#include "Vec.h"

Vec operator+(const Vec& x, const Vec& y) {
    return Vec(x.x + y.x, x.y + y.y);
}

Vec operator*(const double& c, const Vec& y) {
    return Vec(c * y.x, c * y.y);

}

Vec earth_grav(Vec x, const double& t) {
    return Vec(x.x + 0, x.y + 9.8);

}
