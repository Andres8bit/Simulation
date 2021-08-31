#pragma once
#include<math.h>
#include "resource.h"
#include "Sphere.h"
#include "Force.h"
#include<string>
#include <iostream>
#include <tchar.h>
#include <list>
#include"Plane.h"
#include<windowsx.h>

typedef Vec(*force)(Vec, const double&);
typedef Vec(*fx)(Vec);

enum FUNC { CONST_ACC, ACC, VEL };
class Engine {
private:
	float xBounds;
	float yBounds;
	std::list<std::shared_ptr<Obj>> objs;
	std::list<std::shared_ptr<Obj>>::iterator selection;
	double time;
	void apply(Obj& x, FUNC f, double t);



public:
	Engine(float x = 800, float y = 600);
	~Engine();
	void add_obj(Obj& item);
	void step();
	void render(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	BOOL hit_test(float x, float y);
	std::shared_ptr<Obj> Selection();
	void clear_selection() { selection = objs.end(); }
	void set_bounds(float x, float y) { this->xBounds = x; this->yBounds = y; };
};   