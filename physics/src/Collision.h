#pragma once
#include"Sphere.h"
#include"Plane.h"
class Collision
{
public:
	 Vec sphere_to_sphere(Sphere& x, Sphere& y);
     Vec sphere_to_plane(Sphere& x, Plane& y);
};

