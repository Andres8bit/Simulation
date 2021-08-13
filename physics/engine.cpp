#include "engine.h"

Engine::Engine()
{
    this->count = 1;
    this->items = new Obj[this->count];
    this->G = 6.67e-11;
    this->forces.push_back(Vec(0,9.8));// gravitational force on Earth
}
Engine::~Engine(){
    delete[] this->items;
}

void Engine::applyForces(){
    Vec constants = sum_const_force();

    for(int i = 0; i < this->count;i++){

    }
}

Vec Engine::sum_const_force(){
    Vec sum;
   //sum all constant forces acting in the engine:
   //   i.e drag,fluids, or vector forces.
   unsigned int size = this->forces.size();
   for(int i = 0; i < size; i++){
        sum.x += this->forces[i].x;
        sum.y += this->forces[i].y;
   }

   return sum;
}

