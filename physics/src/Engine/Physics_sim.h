#pragma once
#include<math.h>
#include "resource.h"
#include "Sphere.h"
#include<string>
#include <iostream>
#include <tchar.h>
#include <list>
#include"Plane.h"
#include"Triangle.h"
#include"Collision.h"
#include<windowsx.h>

typedef Vec(*force)(Vec, const float&);
typedef Vec(*fx)(Vec);

enum FUNC { CONST_ACC, ACC, VEL };
class Engine {
private:
	float xBounds;
	float yBounds;
	Collision collisions;
	std::list<std::shared_ptr<Obj>> objs;
	std::list<std::shared_ptr<Obj>>::iterator selection;
	float time;
	void apply(Obj& x, FUNC f, float t);
	Vec Impulse() {};
	void collision();



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