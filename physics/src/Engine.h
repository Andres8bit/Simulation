#pragma once
#include "collision.h"
typedef void (*force)(const Obj*&);

class Engine
{
public:
	Engine();
	~Engine();
private:
	Obj* objects;
	size_t capacity; // total number of objects the engine has room for currently
	size_t obj_count; // number of objs in the scene
	size_t force_count; // number of constant forces acting throughout the scene
	Vec* forces; // 2D vector pointer to serve as dynamic array of  force vectors for vectors fields 
	             //i.e Gravity, Air Drag, Viscous fluids

	void applyForces();
	Vec sum_const_force();
	void runge_kutta(force f, double t, Obj*& x, double step_size, double steps);
};
