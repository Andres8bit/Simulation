#include"Collision.h"
#include <iostream>
#include "Vec.h"
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
	size_t force_count; // number of constant forces acting throughout the scene
	Vec* forces; // 2D vector pointer to serve as dynamic array of  force vectors for vectors fields 
	             //i.e Gravity, Air Drag, Viscous fluids

	void resize();
	void applyForces(Obj*& k);
	void G(Obj*&x);
	void frict(Obj*& x,const double &t);
	void vis(Obj*& x);
	Vec vel(const Vec& x,const double& t);
	void earth_gravity_accel(Obj& obj);
	Vec sum_const_force();

	void runge_kutta(Obj*& x, const Vec& f, const double& h, const size_t& n);
	void runge_kutta_system(const Vec& f,Obj*& x, const double& step_size, const double& steps);
};
