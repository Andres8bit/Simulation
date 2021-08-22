#include "Physics_sim.h"

// solves ODE where:
//			f = dx/dt -> f(x,t) 
//			h = step_size 
//          t = time step
//			n = number of steps
//			x = Vec -> init vector. 
//			returns approximate solution as vec
Vec rk4(const Vec& x, force f, const double& t, const double& h, const size_t& n) {
    Vec k1, k2, k3, k4;
    Vec y = Vec(x.x, x.y);

    for (size_t i = 0; i < n; i++) {
        k1 = h * (f(y, t));
        k2 = h * f(y + (0.5 * k1), t + 0.5 * h);
        k3 = h * f(y + (0.5 * k2), t + 0.5 * h);
        k4 = h * f(y + (k3), t + h);
        y = y + 1 / 6 * (k1 + (2 * k2) + (2 * k3) + k4);
    }
    return y;
}

/*Forces:*/
// Earth Graviational force acting on acceleration.
Vec earth_grav(Vec x, const double& t) {
    return Vec(0, 9.8);
}
void grav(Obj& x, force f, double& t) {
    x.set_acc(rk4(x.get_acc(), f, t, t / 10, 10));
}

/*Member Functions:*/
Engine::Engine(){
	obj_count = force_count = time = 0;
	obj_cap = force_cap = 10;
	objects = new Obj[obj_cap];
	forces = new appliedForce[force_cap];
    forces[0] = grav;
}

Engine::~Engine() {
	obj_count = force_count = obj_cap = force_cap = time = 0;
	delete []objects;
	delete[]forces;
}

void Engine::add_obj(Obj obj){
    if (obj_count = obj_cap) {
        resize_obj();
    }
    Obj* temp = new Obj(obj);
    objects[obj_count] = *temp;
    ++obj_count;
}

void Engine::add_focre(appliedForce f){
    if (force_count = force_cap) {
        resize_forces();
    }
    appliedForce* temp = &f;
    forces[force_count] = *temp;
    ++force_count;
}

void Engine::step(){
    double t = time;
    // sloopy double for loop will eventually split into either quad tree or
    // straight up paralization or quad tree + parralization
    for (size_t i = 0; i < obj_count; i++)
        for (size_t j = 0; j < force_cap; j++) {

        }
}
                            /*Helper Functions and Forces:*/
void Engine::resize_forces(){
    size_t s = force_cap * 2;
    appliedForce* temp = new appliedForce[s];
    
    for (size_t i = 0; i < force_count; i++)
        temp[i] = forces[i];
    force_cap = s;
    delete[] forces;

    this->forces = temp;
}
void Engine::resize_obj(){
    size_t s = obj_cap * 2;
    Obj* temp = new Obj[s];

    for (size_t i = 0; i < obj_cap; i++)
        temp[i] = objects[i];

    obj_cap = s;
    delete[]objects;
    this->objects = temp;
}

