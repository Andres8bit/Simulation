#include "Sphere.h"
Sphere::Sphere(const Sphere& s) {
	copy(s);
}

Sphere::Sphere(Vec center, double radius) {
	ui.point.x = center.x;
	ui.point.y = center.y;
	ui.radiusX = ui.radiusY = radius;
	set_type(TYPE::SPHERE);
	color = D2D1::ColorF(D2D1::ColorF::Black, 1.0f);
}

Sphere::Sphere(double xpos, double ypos, double radius) {
	ui.point.x = xpos;
	ui.point.y = ypos;
	ui.radiusX = ui.radiusY = radius;
	set_type(TYPE::SPHERE);
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
	Vec center = s.get_pos();
	double r = s.get_radius();
	ui.point.x = center.x;
	ui.point.y = center.y;
	ui.radiusX = ui.radiusY = r;
	//need to add get color function.
	color = color = D2D1::ColorF(D2D1::ColorF::Black, 1.0f);
	set_mass(s.get_mass());
	set_acc(s.get_acc());
	set_vel(s.get_vel());
}

Bounds Sphere::bounds() {
	Vec center = Vec(this->ui.point.x, this->ui.point.y);
	double r = this->ui.radiusX;

	Vec upperL = center - Vec(r, r);// top Left is center - radius
	Vec lowerR = center + Vec(r, r);// lower right is center + radius 

     return Bounds(upperL, lowerR);
}