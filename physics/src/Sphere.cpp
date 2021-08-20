#include "Sphere.h"

Sphere::Sphere(const Sphere& s) {
	copy(s);

}
Sphere::Sphere(Vec center, double radius) {
	this->ellipse.point.x = center.x;
	this->ellipse.point.y = center.y;
	this->ellipse.radiusX = this->ellipse.radiusY = radius;
	this->set_type(TYPE::SPHERE);
}

Sphere::Sphere(double xpos, double ypos, double radius) {
	ellipse.point.x = xpos;
	ellipse.point.y = ypos;
	ellipse.radiusX = ellipse.radiusY = radius;
	this->set_type(TYPE::SPHERE);
}
Sphere::~Sphere()
{ 
	this->ellipse.point.x = this->ellipse.point.y = ellipse.radiusX = ellipse.radiusY = 0; 

}
void Sphere::step_position() {

}


void Sphere::step_orientation() {
}