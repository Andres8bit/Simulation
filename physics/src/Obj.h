#include"Vec.h"
#pragma once
#include <d2d1.h>
#include<WinUser.h>
#pragma comment(lib, "d2d1")

enum class TYPE { SPHERE, TRIANGLE, PLANE };
class Obj {
public:
    //getters:
    virtual double get_mass()const {};
    virtual TYPE get_type()const {};
    virtual Vec get_vel()const {};
    virtual Vec get_acc()const {};
    //setter:
    virtual void set_mass(double val) {};
    virtual void set_vel(Vec val) {};
    virtual void set_acc(Vec val) {};
    virtual  void set_type(TYPE val) {};
    virtual void set_color(D2D1::ColorF color) {};
    virtual void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush) {};
    virtual BOOL HitTest(float x, float y) {};
  
private:
    virtual void copy(const Obj& x) {};
};
