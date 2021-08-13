#ifndef ENGINE_H
#define ENGINE_H
#include"collisions.h"

class Engine{
public:
    Engine();
    ~Engine();
    void step();

private:
    double G;
    int count;
    Collisions logic;
    Obj* items;

    void applyForces();

};

#endif // ENGINE_H
