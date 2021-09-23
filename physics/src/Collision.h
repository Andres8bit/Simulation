#pragma once
#include"Sphere.h"
#include"Plane.h"
#include<iostream>
#include<vector>
#include <limits>

class Collision
{
private:
	std::vector<Vec> get_normals(const std::vector<Vec>& vertices)const;
	bool seperate_axis_theorem(const std::vector<Vec>& obj1, const std::vector<Vec>& obj2)const;
	bool isSphereObjColliding(Sphere& x, Obj& y);
	bool isSpheresColliding(Sphere& x,Sphere& y);
	Vec getNearestPoint(const Sphere& sphere, const Obj& obj)const;
public:
	 Vec obj_to_obj(Obj& x, Obj& y);
	 Vec sphere_to_sphere(Sphere& x, Sphere& y);
     Vec sphere_to_plane(Sphere& x, Plane& y);
	 Vec  plane_to_plane(Plane& x, Plane& y);
	 bool iscolliding(Obj& x,Obj& y);

};

