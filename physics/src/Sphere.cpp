#include "Sphere.h"


void Sphere::step_position() {

}

void Sphere::apply_force(Vec::force f, const double& time) {
		this->center = this->center.rk4(f,time, time/10, 10);
}

void Sphere::step_orientation() {
}