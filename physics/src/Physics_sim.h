#pragma once
#include "resource.h"
#include "Sphere.h"
#include "Force.h"
#include<string>
#include <iostream>
#include <tchar.h>
#include <list>
#include<windowsx.h>

typedef Vec(*force)(Vec, const double&);
typedef Vec(*fx)(Vec);

enum FUNC { CONST_ACC, ACC, VEL };
class Engine {
private:
	std::list<std::shared_ptr<Sphere>> objs;
	std::list<std::shared_ptr<Sphere>>::iterator selection;
	double time;
	void apply(Sphere& x, FUNC f, double t);
	void clear_selection() { selection = objs.end(); }
	std::shared_ptr<Sphere> Selection() {
		if (selection == objs.end()) {
			return nullptr;
		}
		else {
			return(*selection);
		}
	}

public:
	Engine();
	~Engine();
	void add_obj(Sphere& item);
	void step();
	void render(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
};