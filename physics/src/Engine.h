#pragma once
#include "collision.h"
class Engine
{
public:
	Engine();
	~Engine();
private:
	Obj* objects;
	size_t count;
};

