#pragma once
#include "Obj.h"

class Sphere:public Obj{
private:
    void copy(const Obj& x) { copy(*(Sphere*)&x); };
    void copy(const Sphere& s);
    D2D1_ELLIPSE    ui;

public:
    Sphere(Obj& x) { copy(x); }
    Sphere(const Sphere& s);
    Sphere(Vec center, double radius = 0.5);
    Sphere(double xpos = 0.0, double ypos = 0.0, double radius = 0.5);
    ~Sphere();
    Sphere& operator=(const Sphere& other);

    //getters:
    std::vector<Vec> vertices()const { };
    Vec center_mass()const { return get_pos(); }
    Vec get_pos()const { return Vec(ui.point.x, ui.point.y); };
    double get_mass()const { return mass; };
    double get_radius()const { return ui.radiusX; }
    D2D1_ELLIPSE get_ui() { return ui; }
    
    //setter:
    void set_pos(Vec pos) { ui.point.x = pos.x; ui.point.y = pos.y; }
    void set_raduis(double r) { ui.radiusX = ui.radiusY = r; }
    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
    BOOL HitTest(float x, float y);
    Bounds bounds();
};