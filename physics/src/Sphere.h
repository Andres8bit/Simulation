#pragma once
#include"obj.h"
class Sphere : public Obj {
public:
    Sphere(const Sphere& s) { copy(s); }
    Sphere(Vec center, double radius = 0.5)
    {
        this->center = center; this->r = radius; this->set_type(TYPE::SPHERE);
    }
    Sphere(double xpos = 0.0, double ypos = 0.0, double radius = 0.5)
    {
        this->center.x = xpos; this->center.y = ypos; this->r = radius; this->set_type(TYPE::SPHERE);
    }
    ~Sphere() { this->center.x = this->center.y = 0; }

    Vec get_center()const { return this->center; }
    double get_radius()const { return this->r; }
    void set_center(Vec pos) { this->center = center; }

    void step_position();
    void apply_force(Vec::force f, const double& time);
    void step_orientation();

    void copy(Obj* obj) {
        Sphere* temp = (Sphere*) &obj;
        this->copy(temp);
    }
private:
    Vec center;
    double r;

    void copy(const Sphere& s) {
        this->center = s.get_center();
        this->r = s.get_radius();
    }
};