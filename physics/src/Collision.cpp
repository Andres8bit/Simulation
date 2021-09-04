#include "Collision.h"
Vec Collision::sphere_to_sphere(Sphere& x, Sphere& y) {
	return Vec();
}

Vec Collision::sphere_to_plane(Sphere& x, Plane& y) {
	return Vec();
}

Vec Collision::plane_to_plane(Plane& x, Plane& y) {
	return Vec();
}

//Returns the Vf of x after a collision with y
Vec Collision::obj_to_obj(Obj& x, Obj& y) {
	double mass_dif = x.get_mass() - y.get_mass();
	double mass_sum = x.get_mass() + y.get_mass();

	Vec firstTerm = ((mass_dif) / (mass_sum)) * x.get_vel();
	Vec secondTerm = ((2 * y.get_mass()) / (mass_sum)) * y.get_vel();

	return firstTerm + secondTerm;
}