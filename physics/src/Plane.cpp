#include "Plane.h"

Plane::Plane(double x, double y, double w, double h) {
    Vec uL = Vec(x, y);
    Vec lR = Vec(x+w,y+h);
    this->ui.top = uL.y;
    this->ui.left = uL.x;
    this->ui.bottom = lR.y;
    this->ui.right = lR.x;
   // this->ui = D2D1_RECT_F();
   this->type = TYPE::PLANE;
   this->color = D2D1::ColorF(D2D1::ColorF::Black, 1.0f);
}
Plane::Plane(Vec uL, Vec lR) {
    this->ui.left = uL.x;
    this->ui.top = uL.y;
    this->ui.right = lR.x;
    this->ui.bottom = lR.y;

    this->type = TYPE::PLANE;
//    this->ui = D2D1_RECT_F();
    this->color = D2D1::ColorF(D2D1::ColorF::Black, 1.0f);
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
    Vec lowerR = this->get_dims() + upperL;

    if((x >= upperL.x && x <= lowerR.x) && (y >= upperL.y && y <= lowerR.y ))
            return true;
    return false;
}

Bounds Plane::bounds(){
    return Bounds(this->get_pos(), this->get_dims()); 
}

void Plane::set_pos(Vec pos) {
    Vec del = pos - Vec(this->ui.left, this->ui.top);
    this->ui.left = pos.x;
    this->ui.top = pos.y;
    this->ui.bottom += del.y;
    this->ui.right  += del.x;
}

Vec Plane::get_dims()const
{
    Vec uL = Vec(this->ui.left, this->ui.top);
    Vec lR = Vec(this->ui.right, this->ui.bottom);

    return lR - uL;

}

void Plane::set_dims(double width, double hieght) {
    this->ui.right = this->ui.left + width;
    this->ui.bottom = this->ui.top + hieght;
}

Vec Plane::center_mass()const{
    return Vec();
}

std::vector<Vec> Plane::vertices()const {
    std::vector<Vec> objSides;
    Vec ul = Vec(this->ui.left, this->ui.top);
    Vec lr = Vec(this->ui.right, this->ui.bottom);
    // ur ->  upper right -> (lr.x,ul.y)
    Vec ur = Vec(lr.x, ul.y);
    // ll -> lower left -> (ul.x,lr.y)
    Vec ll = Vec(ul.x, lr.y);

    objSides.push_back(ul);
    objSides.push_back(ll);
    objSides.push_back(lr);
    objSides.push_back(ur);

    return objSides;
}