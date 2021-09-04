#pragma once
#include"Sphere.h"
#include"Plane.h"
class Collision
{
public:
	 Vec obj_to_obj(Obj& x, Obj& y);
	 Vec sphere_to_sphere(Sphere& x, Sphere& y);
     Vec sphere_to_plane(Sphere& x, Plane& y);
	 Vec  plane_to_plane(Plane& x, Plane& y);
	 bool colliding(Bounds x, Bounds y);
};

