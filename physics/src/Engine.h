#pragma once
#include "collision.h"


class Engine
{
public:
	Engine();
	~Engine();
private:
	double time;
	Obj* objects;
	size_t capacity; // total number of objects the engine has room for currently
	size_t obj_count; // number of objs in the scene
	size_t force_count; // number of constant forces acting throughout the scene
	Vec* forces; // 2D vector pointer to serve as dynamic array of  force vectors for vectors fields 
	             //i.e Gravity, Air Drag, Viscous fluids

	void applyForces(Obj*& k);
	void G(Obj*&x);
	void frict(Obj*& x,const double &t);
	void vis(Obj*& x);
	void vel(Obj*& x,const double& t);
	void accel(Obj*& x,const double& t);
	Vec sum_const_force();
	Vec rk4(const Vec& x,const force f,const double& t, const double& h, const size_t& n);
	void runge_kutta(Obj*& x, const Vec& f, const double& h, const size_t& n);
	void runge_kutta_system(const Vec& f,Obj*& x, const double& step_size, const double& steps);
};
