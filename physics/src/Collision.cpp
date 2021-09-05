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

bool Collision::seperate_axis_theorem(const std::vector<Vec>& obj1,const std::vector<Vec>& obj2)const{
	std::vector<Vec> axis1 = this->get_normals(obj1);
	std::vector<Vec> axis2 = this->get_normals(obj2);

	// concatenate both sets of orthogonal normals/ edge normals
	// to iterate over
	axis2.insert(
		axis2.end(),
		std::make_move_iterator(axis1.begin()),
		std::make_move_iterator(axis2.end())
	);

	double max_a_proj = std::numeric_limits<double>::lowest();
	double min_a_proj = std::numeric_limits<double>::infinity();

	double max_b_proj = std::numeric_limits<double>::lowest();
	double min_b_proj = std::numeric_limits<double>::infinity();
	
	double projection = 0.0;
	
	for (auto axis = axis2.begin(); axis != axis2.end(); axis++) {
		
		for (auto vertex = obj1.begin(); vertex != obj1.end(); vertex++) {
			projection = dot(*vertex, *axis);
			min_a_proj = min(min_a_proj, projection);
			max_a_proj = max(max_a_proj, projection);
		}

		for (auto vertex = obj2.begin(); vertex != obj2.end(); vertex++) {
			projection = dot(*vertex, *axis);
			min_b_proj = min(min_b_proj, projection);
			max_b_proj = max(max_b_proj, projection);
		}

		// if projections of each object do not overlap on axis
		// return true -> theres is a seperating axis between the two
		if (max_a_proj >= min_b_proj && max_b_proj >= min_a_proj) {
			return true;
		}
		
	}

	//if out of loop then projections on all axis overlap -> no seperating axis
	return false;
}

std::vector<Vec> Collision::get_normals(const std::vector<Vec>& vertices)const {
	std::vector<Vec> normals;

	for (auto vert = vertices.begin(); vert != vertices.end(); vert++) {
		Vec p1 = *vert;
		Vec p2 = ((vert + 1) == vertices.end()) ? vertices.front() : *(vert + 1);
		Vec edge = p2 - p1;
		Vec edge_normal = Vec(-1 * edge.y, edge.x);
		double mag = magnitude(edge_normal);


		normals.push_back(edge_normal/mag);
	}
	return normals;
}