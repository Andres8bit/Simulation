#include"Sphere.h"
#include <iostream>
#include<Windows.h>
#pragma once

class Engine
{
public:
	Engine();
	~Engine();
	void step();
	void add(Sphere s);
private:
	double time;
	Sphere* objects;
	size_t capacity; // total number of objects the engine has room for currently
	size_t obj_count; // number of objs in the scene

	void resize();
	void applyForces(Obj*& k);
	void G(Obj*&x);
	void frict(Obj*& x,const double &t);
	void vis(Obj*& x);
	void earth_gravity_accel(Obj& obj);

};
