#pragma once
#include "Obj.h"

class Sphere:public Obj{
private:
    void copy(const Obj& x) { copy(*(Sphere*)&x); };
    void copy(const Sphere& s);
    D2D1_ELLIPSE    ui;
    Vec center;
    float radius;

public:
    Sphere(Obj& x) { copy(x); }
    Sphere(const Sphere& s);
    Sphere(Vec center, float radius = 0.5);
    Sphere(float xpos = 0.0, float ypos = 0.0, float radius = 0.5);
    ~Sphere();
    Sphere& operator=(const Sphere& other);

    //getters:
    std::vector<Vec> vertices()const { std::vector<Vec> temp; temp.push_back(center); return temp; };
    Vec center_mass()const { return get_pos(); }
    Vec get_pos()const { return center; };
    float get_mass()const { return mass; };
    float get_radius()const { return radius; }
    D2D1_ELLIPSE get_ui() { return ui; }
    
    //setter:
    void set_pos(Vec pos);
    void set_radius(float r);
    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
    BOOL HitTest(float x, float y);
    Bounds bounds();
};