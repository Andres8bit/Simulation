#ifndef SPHERE_H
#define SPHERE_H
#include"obj.h"
class Sphere: public Obj{
public:
    Sphere(Vec center, double radius = 0.5)
            { this->center = center; this->r = radius;}
    Sphere(double xpos = 0.0,double ypos=0.0,double radius=0.5)
            {this->center.x = xpos; this->center.y = ypos; this->r = radius;}
    ~Sphere(){ this->center.x = this->center.y = 0;}

    void step_position();
    void apply_force();
    void step_orientation();


private:
    Vec center;
    double r;
};

#endif // SPHERE_H
