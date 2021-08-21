#include "Physics_sim.h"
                            /*Member Functions:*/
Engine::Engine(){
	obj_count = force_count = time = 0;
	obj_cap = force_cap = 10;
	objects = new Obj[obj_cap];
	forces = new force[force_cap];
    forces[0] = earth_grav;
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

void Engine::add_focre(force f){
    if (force_count = force_cap) {
        resize_forces();
    }
    force* temp = &f;
    forces[force_count] = *temp;
    ++force_count;
}

void Engine::step(){
    // sloopy double for loop will eventually split into either quad tree or
    // straight up paralization or quad tree + parralization
    for (size_t i = 0; i < obj_count; i++)
        for (size_t j = 0; j < force_cap; j++);
}
                            /*Helper Functions and Forces:*/
void Engine::resize_forces(){
    size_t s = force_cap * 2;
    force* temp = new force[s];
    
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
// solves ODE where:
//			f = dx/dt -> f(x,t) 
//			h = step_size 
//          t = time step
//			n = number of steps
//			x = Vec -> init vector. 
//			returns approximate solution as vec
Vec rk4(const Vec& x, force f, const double& t, const double& h, const size_t& n){
    Vec k1, k2, k3, k4;
    Vec y = Vec(x.x, x.y);

    for (size_t i = 0; i < n; i++){
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
Vec earth_grav(Vec x, const double& t){
    return Vec(0, 9.8);
}
Vec grav(Obj& x, const double& t) {
    Vec base = x.get_acc();
    return Vec(base.x + 0, 9.8);
}
