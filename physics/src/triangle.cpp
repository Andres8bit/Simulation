#include "triangle.h"
Triangle::Triangle(const Vec& a, const Vec& b, const Vec& c) {
	this->A.x = a.x;
	this->A.y = a.y;
	this->B.x = b.x;
	this->B.y = b.y;
	this->C.x = c.x;
	this->C.y = c.y;
}
Triangle::Triangle(const Triangle& other) {
	copy(other);
}

Triangle& Triangle::operator=(const Triangle& other) {
	if (this == &other) {
		return *this;
	}

	copy(other);
	return *this;
}

void Triangle::Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush){
	ID2D1GeometrySink* psink = NULL;
	ID2D1PathGeometry* pGeometry;
	ID2D1Factory* factory;
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr)) {
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
		if (SUCCEEDED(hr)) {
			hr = factory->CreatePathGeometry(&pGeometry);
			if (SUCCEEDED(hr)) {
				hr = pGeometry->Open(&psink);
				if (SUCCEEDED(hr)) {
					psink->BeginFigure(
						this->A,
						D2D1_FIGURE_BEGIN_FILLED
					);

					psink->AddLine(B);
					psink->AddLine(C);
					psink->EndFigure(D2D1_FIGURE_END_CLOSED);
					hr = psink->Close();
				}
				delete psink;
			}
		}
	}

}

BOOL Triangle::HitTest(float x, float y) {
	return false;
}


Bounds Triangle::bounds() {
	return Bounds();
}

void Triangle::copy(const Triangle& other) {
	this->A = other.getA();
	this->B = other.getB();
	this->C = other.getC();

	color = other.get_color();
	set_mass(other.get_mass());
	set_acc(other.get_acc());
	set_vel(other.get_vel());
	type = TYPE::TRIANGLE;
}



std::vector<Vec> Triangle::vertices()const {
	std::vector<Vec> points;
	points.push_back(Vec(A.x, A.y));
	points.push_back(Vec(B.x, B.y));
	points.push_back(Vec(C.x, C.y));

	return points;
}

Vec Triangle::get_pos()const {
	// should return the center point of the triangle.
	return Vec();
}

Vec Triangle::center_mass()const {
	return Vec();
}

void Triangle::set_pos(const Vec pos) {

}