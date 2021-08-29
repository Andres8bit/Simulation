#include"Vec.h"
#pragma once
#include <d2d1.h>
#include<WinUser.h>
#pragma comment(lib, "d2d1")

enum class TYPE { SPHERE, TRIANGLE, PLANE };
class Obj {
public:
    Obj() {};
    Obj(Obj& x) { copy(x); };
    //getters:
    virtual double get_mass()const = 0 ;
    virtual TYPE get_type()const = 0;
    virtual Vec get_vel()const = 0;
    virtual Vec get_acc()const = 0;
    virtual Vec get_pos()const = 0;
    //setter:
    virtual void set_mass(double val) = 0;
    virtual void set_pos(Vec pos) = 0;
    virtual void set_vel(Vec val) = 0;
    virtual void set_acc(Vec val) = 0;
    virtual  void set_type(TYPE val) = 0;
    virtual void set_color(D2D1::ColorF color) = 0;
    virtual void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush) = 0;
    virtual BOOL HitTest(float x, float y) = 0;
    virtual Vec bounds() = 0 ;
  
private:
    virtual void copy(const Obj& x) = 0;
};
