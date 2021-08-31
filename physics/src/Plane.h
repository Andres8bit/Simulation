#include "Obj.h"
#pragma once

class Plane :public Obj
{
    Plane(double x = 0, double y = 0, double w = 1, double h = 1);
    Plane(Vec uL, Vec lR);
    Plane(const Plane& other);
    Plane(const Obj& other);
    Plane& operator=(const Plane& other);

    //Getters:
    Vec get_pos()const { return Vec(this->ui.left,this->ui.top); }
    Vec get_dims()const { return Vec(this->ui.right,this->ui.bottom); }
    D2D1_COLOR_F get_color()const { return this->color; }
    //Setters:
    void set_color(const D2D1_COLOR_F& color) { this->color = color; }
    void set_pos(Vec pos) { this->ui.right = pos.x; this->ui.top = pos.y; }
    void set_dims(Vec dims) { this->ui.right = dims.x; this->ui.bottom = dims.y; }
    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
    BOOL HitTest(float x, float y);
    Bounds bounds();

private:
    void copy(const Obj& x) { copy(*(Plane*)&x); }
    void copy(const Plane& x);
    D2D1_RECT_F ui;
    Vec upperL;
    Vec dims;
};

