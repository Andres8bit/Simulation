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
	float mass_dif = x.get_mass() - y.get_mass();
	float mass_sum = x.get_mass() + y.get_mass();

	Vec firstTerm = ((mass_dif) / (mass_sum)) * x.get_vel();
	Vec secondTerm = ((2 * y.get_mass()) / (mass_sum)) * y.get_vel();

	return firstTerm + secondTerm;
}

bool Collision::seperate_axis_theorem(const std::vector<Vec>& x_vertices, const std::vector<Vec>& y_vertices)const {
	std::vector<Vec> x_edges = get_normals(x_vertices);
	std::vector<Vec> y_edges = get_normals(y_vertices);

	for (auto axis = x_edges.begin(); axis != x_edges.end(); axis = std::next(axis, 1)) {
		float max_x_proj = std::numeric_limits<float>::lowest();
		float min_x_proj = std::numeric_limits<float>::infinity();
		float max_y_proj = std::numeric_limits<float>::lowest();
		float min_y_proj = std::numeric_limits<float>::infinity();

		for (auto x_vertex = x_vertices.begin(); x_vertex != x_vertices.end(); x_vertex = std::next(x_vertex, 1)) {
			float projection = dot(*axis, *x_vertex);
			max_x_proj = max(projection, max_x_proj);
			min_x_proj = min(projection, min_x_proj);
		}

		for (auto y_vertex = y_vertices.begin(); y_vertex != y_vertices.end(); y_vertex = std::next(y_vertex, 1)) {
			float projection = dot(*axis, *y_vertex);
			max_y_proj = max(projection, max_y_proj);
			min_y_proj = min(projection, min_y_proj);
		}

		if (max_x_proj < min_y_proj || min_x_proj > max_y_proj) {
			return true;
		}

	}
	return false;
}

std::vector<Vec> Collision::get_normals(const std::vector<Vec>& vertices) const{
	std::vector<Vec> normals;

	for (int i = 0; i < vertices.size(); i++) {
		Vec start = vertices.at(i);
		Vec end = i + 1 == vertices.size() ? vertices.at(0) : vertices.at(1 + i);

		Vec edge_normal = end - start;
		edge_normal = perp(norm(edge_normal));
		normals.push_back(edge_normal);

	}
	return normals;
}

bool Collision::iscolliding(Obj& x, Obj& y) {

	// base case both objects are convex objects other than spheres.
	if (x.get_type() != TYPE::SPHERE && y.get_type() != TYPE::SPHERE){
		return !this->seperate_axis_theorem(x.vertices(), y.vertices());
	}

	// both objects are spheres
	if (x.get_type() == TYPE::SPHERE && y.get_type() == TYPE::SPHERE) {
		Sphere xSphere = (Sphere)x;
		Sphere ySphere = (Sphere)y;
		return isSpheresColliding(xSphere, ySphere);
	}

	// one object is a sphere
	if (x.get_type() == TYPE::SPHERE) {
		Sphere temp = x;
		return isSphereObjColliding(temp, y);
	}
	else {
		Sphere temp = y;
		return isSphereObjColliding(temp, x);
	}
}

bool Collision::isSphereObjColliding(Sphere& x, Obj& y) {

	Vec center = x.get_pos();
	float radius = x.get_radius();
	Vec nearest; 
	Vec axis; 
	Vec radiusOffset;
	Vec centerPlusOffset;
	Vec centerMinusOffset;
	std::vector<Vec> vertices = y.vertices();
	std::vector<Vec> edge_normals = get_normals(vertices);
	float max_obj_proj = std::numeric_limits<float>::lowest();
	float min_obj_proj = std::numeric_limits<float>::infinity();
	float max_sphere_proj = std::numeric_limits<float>::lowest();
	float min_sphere_proj = std::numeric_limits<float>::infinity();


	//now check along the axis created using the center of the circle
	// to the nearest point in the other shape.
	max_obj_proj = std::numeric_limits<float>::lowest();
	min_obj_proj = std::numeric_limits<float>::infinity();
	max_sphere_proj = std::numeric_limits<float>::lowest();
	min_sphere_proj = std::numeric_limits<float>::infinity();
	nearest = getNearestPoint(x, y);
	axis = nearest - center;
	axis = norm(axis);

	// get circle projections
	Vec direction = axis;
	radiusOffset = radius * direction;
	centerPlusOffset = center + radiusOffset;
	centerMinusOffset = center - radiusOffset;
	max_sphere_proj = dot(axis, centerMinusOffset);
	min_sphere_proj = dot(axis, centerPlusOffset);
	if (max_sphere_proj < min_sphere_proj) {
		float temp = min_sphere_proj;
		min_sphere_proj = max_sphere_proj;
		max_sphere_proj = temp;
	}


	for (auto vertex = vertices.begin(); vertex != vertices.end(); vertex = std::next(vertex, 1)) {
		float projection = dot(axis, *vertex);
		max_obj_proj = max(max_obj_proj, projection);
		min_obj_proj = min(min_obj_proj, projection);
		if (max_sphere_proj < min_obj_proj || min_sphere_proj > max_obj_proj) {
			return false;
		}

	}





	for (auto obj_axis = edge_normals.begin(); obj_axis != edge_normals.end(); obj_axis = std::next(obj_axis, 1)) {

		// get the largest and smalled project of the obj along each axis
		for (auto vertex = vertices.begin(); vertex != vertices.end(); vertex = std::next(vertex, 1)) {
			float vert_projection = dot(*obj_axis, *vertex);
			max_obj_proj = max(max_obj_proj, vert_projection);
			min_obj_proj = min(min_obj_proj, vert_projection);
		}
		// project each "edge" from the center to outer edge of  circle
		// then return largest and smallest projections.
		Vec direction = norm(*obj_axis);
		radiusOffset = radius * direction;

		centerPlusOffset = center + radiusOffset;
		centerMinusOffset = center - radiusOffset;

		max_sphere_proj = dot(*obj_axis, centerMinusOffset);
		min_sphere_proj = dot(*obj_axis, centerPlusOffset);

		if (max_sphere_proj < min_sphere_proj) {
			float temp = min_sphere_proj;
			min_sphere_proj = max_sphere_proj;
			max_sphere_proj = temp;
		}

		if (max_sphere_proj < min_obj_proj || min_sphere_proj > max_obj_proj) {
			return false;
		}
	}

	return true;
}

bool Collision::isSpheresColliding(Sphere& x, Sphere& y) {
	float radDist = abs(x.get_radius() + y.get_radius());

	float centerDistance = distance(x.get_pos(), y.get_pos());

	return radDist >= centerDistance;
}

Vec Collision::getNearestPoint(const Sphere& sphere, const Obj& obj)const {
	float minDist = std::numeric_limits<float>::infinity();
	std::vector<Vec> vertices = obj.vertices();
	Vec center = sphere.get_pos();
	Vec nearest;
	size_t n = vertices.size();

	for (size_t i = 0; i < n; i++) {
		float temp = distance(center, vertices.at(i));
		minDist = min(temp, minDist);
		nearest = minDist == temp ? vertices.at(i) : nearest;
	}

	return nearest;
}