#pragma once
#include "resource.h"
#include "obj.h"
#include "Force.h"
#include<string>
#include <iostream>
class Engine {
private:
	void resize_forces();
	void resize_obj();

	std::list<std::shared_ptr<Obj>> objs;
	double time;
public:
	Engine();
	~Engine();
	void add_obj(Obj item);
	void step();
};