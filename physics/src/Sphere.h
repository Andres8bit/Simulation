#pragma once
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include"obj.h"
class Sphere : public Obj {
public:
    Sphere(const Sphere& s);
    Sphere(Vec center, double radius = 0.5);
    Sphere(double xpos = 0.0, double ypos = 0.0, double radius = 0.5);
    ~Sphere();
    Vec get_center()const { return Vec(this->ellipse.point.x,this->ellipse.point.y); }
    double get_radius()const { return this->ellipse.radiusX; }
    void set_center(Vec pos) { this->ellipse.point.x = pos.x; this->ellipse.point.y = pos.y; }
    void step_position();
    void step_orientation();
private:
    D2D1_ELLIPSE ellipse;
    D2D1_COLOR_F color;

    void copy(const Sphere& s) {
        Vec center(s.get_center());
        this->ellipse.point.x = center.x;
        this->ellipse.point.y = center.y;
        this->ellipse.radiusX = this->ellipse.radiusY = s.get_radius();
        this->set_type(s.get_type());
    }
};