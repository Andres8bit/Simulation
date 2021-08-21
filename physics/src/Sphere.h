#pragma once
#include "Obj.h"
class Sphere :
    public Obj
{
private:
    Vec center;
    double radius;
    void copy(const Sphere& s);
public:
    Sphere(const Sphere& s);
    Sphere(Vec center, double radius = 0.5);
    Sphere(double xpos = 0.0, double ypos = 0.0, double radius = 0.5);
    ~Sphere();
    Vec get_center()const { return Vec(this->center.x, this->center.y); }
    double get_radius()const { return this->radius; }
    void set_center(Vec pos) { this->center.x = pos.x; this->center.y = pos.y; }
    void step_position();
    void step_orientation();

};

