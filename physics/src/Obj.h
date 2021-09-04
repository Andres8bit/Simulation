#include "Bounds.h"
#pragma once
#include <d2d1.h>
#include<WinUser.h>
#pragma comment(lib, "d2d1")

enum class TYPE { BASE,SPHERE, TRIANGLE, PLANE };
class Obj {
public:
    Obj();
    Obj(Obj& x) { copy(x); };
    //getters:
    virtual Vec get_pos()const = 0;
    virtual Vec center_mass()const = 0;
    double get_mass()const { return this->mass; }
    TYPE get_type()const { return this->type; }
    Vec get_vel()const { return this->vel; }
    Vec get_acc()const { return this->acc; }
    Vec linear_momentum()const { return this->mass * this->vel; }
    Vec rotation()const { return this->angle_of_rotation; }
    D2D1_COLOR_F get_color()const { return this->color; }
    //setter:
    virtual void set_pos(const Vec pos) = 0;
    void set_mass(double val) { this->mass = val; }
    void set_vel(Vec val) { this->vel = val; }
    void set_acc(Vec val) { this->acc = val; }
    void set_type(TYPE val) { this->type = val; }
    void set_color(D2D1::ColorF color) { this->color = color; }
    virtual void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush) = 0;
    virtual BOOL HitTest(float x, float y) = 0;
    virtual Bounds bounds() = 0 ;
  
private:
    virtual void copy(const Obj& x) = 0;
protected:
    D2D1_COLOR_F    color;
    Vec vel;
    Vec acc;
    double mass;
    double angle_of_rotation;
    TYPE type;
};
