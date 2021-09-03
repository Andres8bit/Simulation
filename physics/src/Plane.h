#include "Obj.h"
#pragma once

class Plane: public Obj
{
public:
    //(x,y) -> upper left
    //(w,h) -> width 7 hieght of plane
    Plane(double x = 0, double y = 0, double w = 1, double h = 1);
    Plane(Vec& uL, Vec& lR);
    Plane(const Plane& other);
    Plane(const Obj& other);
    Plane& operator=(const Plane& other);

    //Getters:
    Vec get_pos()const { return this->upperL; }
    Vec get_dims()const { return this->dims; }
    D2D1_COLOR_F get_color()const { return this->color; }
    //Setters:
    void set_color(const D2D1_COLOR_F& color) { this->color = color; }
    void set_pos(Vec pos) { this->ui.right = pos.x; this->ui.top = pos.y; }
    void set_dims(Vec dims) { this->ui.right = this->lowerR.x = dims.x; this->ui.bottom = this->lowerR.y =  dims.y; }
    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
    BOOL HitTest(float x, float y);
    Bounds bounds();

private:
    void copy(const Obj& x) { copy(*(Plane*)&x); }
    void copy(const Plane& x);
    D2D1_RECT_F ui;
    Vec upperL;
    Vec lowerR;
    Vec dims;
};

