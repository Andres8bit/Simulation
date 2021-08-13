#include "engine.h"

Engine::Engine()
{
    this->count = 1;
    this->items = new Obj[this->count];
}
Engine::~Engine(){
    delete[] this->items;
}

void Engine::applyForces(){

}
