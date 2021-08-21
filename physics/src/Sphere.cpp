#include "Sphere.h"

Sphere::Sphere(const Sphere& s) {
	copy(s);
}

Sphere::Sphere(Vec center, double radius) {
	this->center.x = center.x;
	this->center.y = center.y;
	this->radius = radius;
	this->set_type(TYPE::SPHERE);
}

Sphere::Sphere(double xpos, double ypos, double radius) {
	this->center.x = xpos;
	this->center.y = ypos;
	this->radius = radius;
	this->set_type(TYPE::SPHERE);
}
Sphere::~Sphere()
{
	this->center.x = this->center.y = this->radius = 0.0;

}
void Sphere::step_position() {

}


void Sphere::step_orientation() {
}

void Sphere::copy(const Sphere& s){
	this->center = s.get_center();
	this->radius = s.get_radius();
	this->set_mass(s.get_mass());
	this->set_acc(s.get_acc());
	this->set_vel(s.get_vel());
}