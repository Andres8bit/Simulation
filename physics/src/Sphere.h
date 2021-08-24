#pragma once
#include "Obj.h"

class Sphere:public Obj{
private:
    D2D1_ELLIPSE    ui;
    D2D1_COLOR_F    color;
    void copy(const Sphere& s);
    Vec acc;
    Vec vel;
    double mass;
    TYPE type;
public:
    Sphere(const Sphere& s);
    Sphere(Vec center, double radius = 0.5);
    Sphere(double xpos = 0.0, double ypos = 0.0, double radius = 0.5);
    ~Sphere();
    //getters:
    double get_mass()const { return mass; };
    TYPE get_type()const { return type; };
    Vec get_vel()const { return vel; };
    Vec get_acc()const { return acc; };
    Vec get_center()const { return Vec(ui.point.x, ui.point.y); }
    double get_radius()const { return ui.radiusX; }
    //setter:

    void set_mass(double val) { mass = val; }
    void set_vel(Vec val) { vel = val; };
    void set_acc(Vec val) { acc = val; };
    void set_type(TYPE val) { type = val; };
    void set_center(Vec pos) { ui.point.x = pos.x; ui.point.y = pos.y; }
    void set_raduis(double r) { ui.radiusX = ui.radiusY = r; }

    D2D1_ELLIPSE get_ui() { return ui; }
    void set_color(D2D1::ColorF color) { this->color = color; }
    void apply_force(Vec::force f);
    void step_position();
    void step_orientation();
    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
    BOOL HitTest(float x, float y);
};