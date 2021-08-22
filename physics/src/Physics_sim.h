#pragma once
#include "resource.h"
#include "obj.h"


typedef Vec(*force)(Vec, const double&);
typedef void(*appliedForce)(Obj&, force, double&);

class Engine {
private:
	void resize_forces();
	void resize_obj();

	Obj* objects;
	appliedForce* forces;
	size_t obj_count;
	size_t force_count;
	size_t obj_cap;
	size_t force_cap;
	double time;
public:
	Engine();
	~Engine();
	void add_obj(Obj item);
	void add_focre(appliedForce f);
	void step();
};