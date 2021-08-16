#include "Engine.h"
//init all forces and objects in current scene:
//   For assume Earth model with constant forces G = (0,9.8) -> positive because we want y = 0 to be the sky
//
Engine::Engine()
{
	this->capacity = 10;
	this->obj_count = 0;
	this->force_count = 1;
	this->objects = new Obj[capacity];
	this->forces = new Vec[capacity];

	//init Gravitationoal force on earth. Newtonian Model
	this->forces[0].x = 0; // applies no forces in the x
	this->forces[0].y = 9.8; // applies constant force in the y direction.

}

Engine::~Engine()
{
	//deallocate memory
	delete[] this->forces;
	delete[] this->objects;
}

void Engine::runge_kutta(force f, double t, Obj*& x, double step_size, double steps) {


}

void Engine::applyForces() {
	Vec fields = this->sum_const_force();

	// For each object apply the forces within the scene:
	for (size_t i = 0; i < this->obj_count; i++) {
		//call runge-kutta to apply forces on each object
	
	}
}

Vec Engine::sum_const_force() {
	Vec sum;
	for (size_t i = 0; i < this->force_count; i++) {
		sum.x += this->forces[i].x;
		sum.y += this->forces[i].y;
	}

	return sum; // return the total sum of forces acting in each dimension.

}