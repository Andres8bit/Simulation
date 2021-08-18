#pragma once
#include "Vec.h"
enum class TYPE {SPHERE, TRIANGLE, PLANE };
class Obj {
public:
     Obj() {}
    ~Obj() {}
     

    void step(double t) {}
    //getters:
    double get_mass() { return this->mass; }
    TYPE get_type() { return this->t; }
    Vec get_vel() { return this->vel; }
    Vec get_acc() { return this->acc; }

    //setter:
    void set_mass(double val) { this->mass = val; }
    void set_vel(Vec val) { this->vel = val; }
    void set_acc(Vec val) { this->acc = val; }
    void set_type(TYPE val) { this->t = val; }
    virtual void apply_force(Vec::force f,const double& time) {};
    virtual void copy(Obj*) {};
private:
    double mass;
    Vec vel;
    Vec acc;
    TYPE t;
};

