#pragma once
#include "resource.h"
#include "obj.h"


typedef Vec (*force)(Vec, const double&);
typedef Vec(*test)(Obj&, const double&);
Vec earth_grav(Vec x, const double& t);
Vec grav(Obj& x, const double& t);
Vec rk4(const Vec& x, force f, const double& t, const double& h, const size_t& n);

class Engine {
private:
	void resize_forces();
	void resize_obj();
	void apply_earth_grav(Obj& x);



	Obj* objects;
	force* forces;
	size_t obj_count;
	size_t force_count;
	size_t obj_cap;
	size_t force_cap;
	double time;
public:
	Engine();
	~Engine();
	void add_obj(Obj item);
	void add_focre(force f);
	void step();
};