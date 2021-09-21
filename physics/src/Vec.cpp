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
    return sqrt(lenSqrd(x));
}

Vec operator/(const Vec& y, const double& x) {
    if (x != 0) {
        return Vec(y.x / x, y.y / x);
    }
    return y;
}

double distance(const Vec& x, const Vec& y) {
    double xDel = (y.x - x.x) * (y.x - x.x);
    double yDel = (y.y - x.y) * (y.y - y.x);

    return sqrt(xDel + yDel);
}

Vec inverse(const Vec& x) {
    return Vec(-x.x, -x.y);
}

Vec polar(const double& angle,const double& radius){
    return Vec(radius * cos(angle), radius * sin(angle));
}

double angle(const Vec& x){
    return  atan2(x.y, x.x);
}

Vec norm(const Vec& x) {
    return x / magnitude(x);
}

Vec translate(const Vec& x, const double& tx, const double& ty) {
    return Vec(x.x + tx, x.y + ty);
}

Vec rotate(const Vec& x, const float& rad) {
    new Vec(x.x * cos(rad) - x.y * sin(rad), x.x * sin(rad) + x.y * cos(rad));
}

Vec shear(const Vec&x, const float& sx, const float& sy) {
    return Vec(x.x + sx * x.y, x.y + sy * x.x);
}

double lenSqrd(const Vec& x){
    return x.x *x.x  + x.y * x.y;
}

Vec perp(const Vec& x) {
    return Vec(-x.y, x.x);
}

Vec scale(const Vec& x, const double& sx, const double& sy) {
    return Vec(x.x * sx, x.y * sy);
}