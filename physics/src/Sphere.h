#pragma once
#include "Obj.h"
#include <d2d1.h>
#include<WinUser.h>
#pragma comment(lib, "d2d1")
class Sphere :
    public Obj
{
private:
    D2D1_ELLIPSE    ui;
    D2D1_COLOR_F    color;
    void copy(const Sphere& s);
public:
    Sphere(const Sphere& s);
    Sphere(Vec center, double radius = 0.5);
    Sphere(double xpos = 0.0, double ypos = 0.0, double radius = 0.5);
    ~Sphere();
    Vec get_center()const { return Vec(ui.point.x,ui.point.y); }
    double get_radius()const { return ui.radiusX; }
    void set_center(Vec pos) { ui.point.x = pos.x; ui.point.y = pos.y; }
    void set_raduis(double r) { ui.radiusX = ui.radiusY = r; }
    void step_position();
    void step_orientation();
    D2D1_ELLIPSE get_ui() { return ui; }
    void set_color(D2D1::ColorF color) { this->color = color; }
    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
    BOOL HitTest(float x, float y);
};

