#include "Sphere.h"
Sphere::Sphere(const Sphere& s) {
	copy(s);
}

Sphere::Sphere(Vec center, float radius) {
	this->center = center;
	this->radius = radius;
	ui.point.x = center.x;
	ui.point.y = center.y;
	ui.radiusX = ui.radiusY = radius;
	this->type = TYPE::SPHERE;
	color = D2D1::ColorF(D2D1::ColorF::Black, 1.0f);
}

Sphere::Sphere(float xpos, float ypos, float radius) {
	this->center = Vec(xpos, ypos);
	this->radius = radius;
	ui.point.x = xpos;
	ui.point.y = ypos;
	ui.radiusX = ui.radiusY = radius;
	this->type = TYPE::SPHERE;
	color = D2D1::ColorF(D2D1::ColorF::Black, 1.0f);
}
Sphere::~Sphere()
{
	ui.point.x = ui.point.y = ui.radiusX = ui.radiusY = 0.0;

}

Sphere& Sphere::operator=(const Sphere& other) {
	if (this == &other)
		return *this;

	copy(other);
	return *this;
}

void Sphere::Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush) {
	pBrush->SetColor(color);
	pRT->FillEllipse(ui, pBrush);
	pRT->DrawEllipse(ui, pBrush, 1.0f);
}


BOOL Sphere:: HitTest(float x, float y) {
	const float a = ui.radiusX;
	const float b = ui.radiusY;
	const float x1 = x - ui.point.x;
	const float y1 = y - ui.point.y;
	const float d = ((x1 * x1) / (a * a)) + ((y1 * y1) / (b * b));
	return d <= 1.0f;
}

void Sphere::copy(const Sphere& s){
	this->center = s.get_pos();
	this->radius = s.get_radius();
	this->ui.point.x = this->center.x;
	this->ui.point.y = this->center.y;
	this->ui.radiusX = this->ui.radiusY = this->radius;

	color = s.get_color();
	set_mass(s.get_mass());
	set_acc(s.get_acc());
	set_vel(s.get_vel());
	type = TYPE::SPHERE;
}

Bounds Sphere::bounds() {
	Vec center = Vec(this->ui.point.x, this->ui.point.y);
	float r = this->ui.radiusX;

	Vec upperL = center - Vec(r, r);// top Left is center - radius
	Vec lowerR = center + Vec(r, r);// lower right is center + radius 

     return Bounds(upperL, lowerR);
}

void Sphere::set_pos(Vec pos){ 
	center.x = pos.x;
	ui.point.x = pos.x;
	center.y = pos.y;
	ui.point.y = pos.y;
}

void Sphere::set_radius(float r) {
	radius = r; 
	ui.radiusX = ui.radiusY = r; }