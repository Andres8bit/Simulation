#include "triangle.h"
Triangle::Triangle(const Vec& a, const Vec& b, const Vec& c) {
	this->A.x = a.x;
	this->A.y = a.y;
	this->B.x = b.x;
	this->B.y = b.y;
	this->C.x = c.x;
	this->C.y = c.y;

	this->color = D2D1::ColorF(D2D1::ColorF::Black, 1.0f);
}

Triangle::Triangle(const Vec& a, const Vec& b) {
	this->A.x = a.x;
	this->A.y = a.y;
	this->B.x = b.x;
	this->B.y = b.y;
	// analytical solution for third point of equilateral triangle.
	this->C.x = 0.5 * ((double)b.x + a.x) + (sqrt(3) / 2) * ((double)b.y - a.y);
	this->C.y = 0.5 * ((double)b.y + a.y) + (sqrt(3) / 2) * ((double)b.x - a.x);
	
	this->color = D2D1::ColorF(D2D1::ColorF::Black, 1.0f);
}


Triangle::Triangle(const Triangle& other) {
	copy(other);
}
Triangle::Triangle(const Obj& other) {
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
					D2D1_POINT_2F pointA = VecToD2D1(A);
					D2D1_POINT_2F pointB = VecToD2D1(B);
					D2D1_POINT_2F pointC = VecToD2D1(C);
					psink->BeginFigure(
						 pointA,
						D2D1_FIGURE_BEGIN_FILLED
					);
					psink->AddLine(pointB);
					psink->AddLine(pointC);
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

}



std::vector<Vec> Triangle::vertices()const {
	std::vector<Vec> points;
	points.push_back(Vec(A.x, A.y));
	points.push_back(Vec(B.x, B.y));
	points.push_back(Vec(C.x, C.y));

	return points;
}

Vec Triangle::get_pos()const {
	double height = abs(A.y - C.y);

	return Vec(C.x, 0.5 * (height));
}

Vec Triangle::center_mass()const {
	return Vec();
}

void Triangle::set_pos(const Vec pos) {
	Vec diff = pos - this->get_pos();

	this->A = A + diff;
	this->B = B + diff;
	this->C = C + diff;

}
