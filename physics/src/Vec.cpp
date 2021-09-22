#include "Vec.h"

Vec operator+(const Vec& x, const Vec& y) {
    return Vec(x.x + y.x, x.y + y.y);
}

Vec operator*(const float& c, const Vec& y) {
    return Vec(c * y.x, c * y.y);

}

Vec operator-(const Vec& x, const Vec& y) {
    return Vec(x.x - y.x, x.y - y.y);
}

float dot(const Vec& x, const Vec& y){ 
    return (x.x * y.x) + (x.y * y.y); 
}

float magnitude(const Vec& x) {
    return sqrt(lenSqrd(x));
}

Vec operator/(const Vec& y, const float& x) {
    if (x != 0) {
        return Vec(y.x / x, y.y / x);
    }
    return y;
}

float distance(const Vec& x, const Vec& y) {
    float xx = x.x;
    float xy = x.y;
    float yx = y.x;
    float xDel = (y.x - x.x);
    float yDel = (y.y - x.y);
    float xDel2 = xDel * xDel;
    float yDel2 = yDel * yDel;
    float temp = sqrt(xDel2 + yDel2);

    return sqrt(xDel2 + yDel2);
}

Vec inverse(const Vec& x) {
    return Vec(-x.x, -x.y);
}

Vec polar(const float& angle,const float& radius){
    return Vec(radius * cos(angle), radius * sin(angle));
}

float angle(const Vec& x){
    return  atan2(x.y, x.x);
}

Vec norm(const Vec& x) {
    return x / magnitude(x);
}

Vec translate(const Vec& x, const float& tx, const float& ty) {
    return Vec(x.x + tx, x.y + ty);
}

Vec rotate(const Vec& x, const float& rad) {
    return Vec(x.x * cos(rad) - x.y * sin(rad), x.x * sin(rad) + x.y * cos(rad));
}

Vec shear(const Vec&x, const float& sx, const float& sy) {
    return Vec(x.x + sx * x.y, x.y + sy * x.x);
}

float lenSqrd(const Vec& x){
    return x.x *x.x  + x.y * x.y;
}

Vec perp(const Vec& x) {
    return Vec(-x.y, x.x);
}

Vec scale(const Vec& x, const float& sx, const float& sy) {
    return Vec(x.x * sx, x.y * sy);
}