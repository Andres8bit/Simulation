#include "Plane.h"
Plane::Plane(double x, double y, double w,double h)
 {
    this->upperL = Vec(x, y);
    this->dims = Vec(w, h);

}

Plane::Plane(Vec uL, Vec width_hieght) {
    this->upperL = uL;
    this->dims = width_hieght;
}

Plane::Plane(const Plane& other) {

}

Plane::Plane(const Obj& other) {

}

Plane& Plane::operator=(const Plane& other) {

}