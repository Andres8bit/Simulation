#include "Engine.h"

//init all forces and objects in current scene:
//   For assume Earth model with constant forces G = (0,9.8) -> positive because we want y = 0 to be the sky
//
Engine::Engine()
{
	this->capacity = 10;
	this->obj_count = 0;
	this->objects = new Sphere[capacity];	
}

Engine::~Engine()
{
	//deallocate memory
	delete[] this->objects;
}
void Engine::step() {
	for (int i = 0; i < this->obj_count; i++) {
		this->earth_gravity_accel(objects[i]);
	}
}



void Engine::applyForces(Obj*& k) {

	
}




// Constant force def:
// Missing Vector force def i.e generic ODE applications
void Engine::G(Obj*& x) {

}

void Engine::frict(Obj*& x,const double& t) {


}
void Engine::vis(Obj*& x) {

}



void Engine::earth_gravity_accel(Obj& obj) {
	double h = this->time / 10;
	double n = 10;
}


void Engine::add(Sphere s) {
	Sphere* temp  = new Sphere(s);
	if (obj_count < capacity) {
		(objects[obj_count]) = *temp;
		obj_count++;
	
		std::cout << "added" << std::endl;
	}else {
		this->resize();
	}

}

void Engine::resize() {

}
