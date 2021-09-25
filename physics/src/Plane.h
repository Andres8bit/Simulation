#include "Obj.h"
#include <math.h>
#pragma once

class Plane: public Obj
{
public:
    //(x,y) -> upper left
    //(w,h) -> width & hieght of plane
    Plane(float x = 0, float y = 0, float w = 1, float h = 1);
    // uL -> upper left point of plane
    // lR -> lower right point of plane
    Plane(Vec uL, Vec lR);
    Plane(const Plane& other);
    Plane(const Obj& other);
    Plane& operator=(const Plane& other);

    //Getters:
    TYPE get_type() { return TYPE::PLANE; }
    std::vector<Vec> vertices()const;
    Vec center_mass()const;
    // returns the upper left point
    Vec get_pos()const { return Vec(this->ui.left, this->ui.top); }
    //returns the width and hieght of the plane as a 2D Vec (w,h)
    Vec get_dims()const;
    D2D1_COLOR_F get_color()const { return this->color; }
    //Setters:
    void set_color(const D2D1_COLOR_F& color) { this->color = color; }
    
    // sets the upper left point of plane 
    // and resets lower right point
    // in keeping with change to upperL and dims
    void set_pos(Vec pos);
    void set_dims(float width, float hieght);
    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
    BOOL HitTest(float x, float y);
    Bounds bounds();

private:
    void copy(const Obj& x) { copy(*(Plane*)&x); }
    void copy(const Plane& x);
    D2D1_RECT_F ui;

};

