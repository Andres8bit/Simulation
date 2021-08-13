#ifndef ENGINE_H
#define ENGINE_H
#include"collisions.h"
#include<vector>

class Engine{
public:
    Engine();
    Engine(Vec forces,Obj* item_list, size_t count);
    ~Engine();

    void step();
    void add_force_field(Vec field)
        {this->forces.push_back(field);}
private:
    //vector of forces, where each forec as a x and y component.
    std::vector<Vec> forces;
    double G;
    int count;
    Collisions logic;
    Obj* items;

    void applyForces();
    Vec sum_const_force();

};

#endif // ENGINE_H
