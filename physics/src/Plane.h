#include "Obj.h"
#pragma once

class Plane :public Obj
{
    Plane(double x = 0, double y = 0, double w = 1, double h = 1);
    Plane(Vec uL, Vec width_hieght);
    Plane(const Plane& other);
    Plane(const Obj& other);
    Plane& operator=(const Plane& other);
    double get_mass()const;
    TYPE get_type()const;
    Vec get_vel()const;
    Vec get_acc()const;
    Vec get_pos()const;
    //setter:
    void set_mass(double val);
    void set_pos(Vec pos);
    void set_vel(Vec val);
    void set_acc(Vec val);
    void set_type(TYPE val);
    void set_color(D2D1::ColorF color);
    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
    BOOL HitTest(float x, float y);
    Vec bounds();

private:
    void copy(const Obj& x) { copy(*(Plane*)&x); }
    void copy(const Plane& x);
    Vec vel;
    double mass;
    TYPE type;
    Vec upperL;
    Vec dims;
};

