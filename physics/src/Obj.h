#include"Vec.h"
#pragma once

enum class TYPE { SPHERE, TRIANGLE, PLANE };
class Obj {
public:
    Obj();
    Obj(const Obj& x);
    ~Obj();

    void step(double t) {}
    //getters:
    double get_mass()const { return this->mass; }
    TYPE get_type()const { return this->t; }
    Vec get_vel()const { return this->vel; }
    Vec get_acc()const { return this->acc; }

    //setter:
    void set_mass(double val) { this->mass = val; }
    void set_vel(Vec val) { this->vel = val; }
    void set_acc(Vec val) { this->acc = val; }
    void set_type(TYPE val) { this->t = val; }
private:
    void copy(const Obj& x);
    double mass;
    Vec vel;
    Vec acc;
    TYPE t;
};
