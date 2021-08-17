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

void Engine::runge_kutta_system(const Vec& f, Obj*& x, const double& step_size,const double& steps) {
	// init 2d dynamic array. Each row serces as order
	Obj** K = new Obj*[4]; 
	Obj* Y = new Obj[this->obj_count];

	// init each order vector to hold values at each order
	for (int i = 0; i < 4; i++) 
		K[i] = new Obj[this->obj_count];
	

	for (int i = 0; i < steps; i++){	
		// 1st order setup:
		applyForces(K[0]);

		// 2nd order setup:
		applyForces(K[1]);

		// 3rd order setup:
		applyForces(K[2]);

		// 4th order setup:
		applyForces(K[3]);
	}

}

void Engine::applyForces(Obj*& k) {
	Vec fields = this->sum_const_force();

	// For each object apply the forces within the scene:
	for (size_t i = 0; i < this->obj_count; i++) {
		// call overridden virtual function apply force.
		// this allows each pointer to call the appropriate
		// apply_force method.
		k[i].apply_force(fields);
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


// Constant force def:
// Missing Vector force def i.e generic ODE applications
void Engine::G(Obj*& x) {

}

void Engine::frict(Obj*& x,const double& t) {


}
void Engine::vis(Obj*& x) {

}

Vec Engine::vel(const Vec& x,const double& t) {
	Vec vel;
	vel.x = x.x + x.x *t;
	vel.y = x.y + x.y *t;
	return vel;
}

Vec Engine::accel(const Vec& x,const double& t) {
	Vec acc;
	return acc;
}