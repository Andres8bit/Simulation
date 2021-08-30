#include "Plane.h"
Plane::Plane(double x, double y, double w,double h)
 {
    this->ui.left = x;
    this->ui.top = y;
    this->ui.right = w;
    this->ui.bottom = h;
    this->mass = 0.0;
    this->vel = Vec();
    this->acc = Vec();
    this->type = TYPE::PLANE;
}

Plane::Plane(Vec uL, Vec lR) {
    this->ui.left = uL.x;
    this->ui.top = uL.y;
    this->ui.right = lR.x;
    this->ui.bottom = lR.y;
    this->mass = 0.0;
    this->vel = Vec();
    this->acc = Vec();
    this->type = TYPE::PLANE;
}

Plane::Plane(const Plane& other) {
    copy(other);
}

Plane::Plane(const Obj& other) {
    copy(other);
}

Plane& Plane::operator=(const Plane& other) {
    if (this == &other)
        return *this;
    copy(other);
    return *this;
}


void Plane::copy(const Plane& x) {
    Vec dims = x.get_dims();
    Vec pos = x.get_pos();

    this->acc = x.get_acc();
    this->mass = x.get_mass();
    this->vel = x.get_vel();
    this->type = x.get_type();
    this->ui.left = pos.x;
    this->ui.top = pos.y;
    this->ui.right = dims.x;
    this->ui.bottom = dims.y;
    this->color = x.get_color();
}

void Plane::Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush) {
    pBrush->SetColor(this->color);
    pRT->FillRectangle(this->ui, pBrush);
    pRT->DrawRectangle(this->ui, pBrush);
}

BOOL Plane::HitTest(float x, float y) { 
    Vec upperL = this->get_pos();
    Vec lowerR = this->get_dims();

    if((x < upperL.x || x > lowerR.x) && (y < upperL.y || y > lowerR.y ))
            return false;
    return true;
}

Bounds Plane::bounds(){
    return Bounds(this->get_pos(), this->get_dims()); 
}

