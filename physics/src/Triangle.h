#pragma once
#include "Obj.h"
#include<wrl.h>
#include"Utils.h"

class Triangle :public Obj{
public:
	Triangle(const Vec& a, const Vec& b, const Vec& c);
	Triangle(const Vec& a, const Vec& b);
	Triangle(const Triangle& other);
	Triangle(const Obj& other);
	Triangle& operator=(const Triangle& other);
	
	TYPE get_type() { return TYPE::TRIANGLE; }
	std::vector<Vec> vertices()const;
	Vec get_pos()const;
	Vec center_mass()const;
	void set_pos(const Vec pos);
	Vec getA()const { return A; }
	Vec getB()const { return B; }
	Vec getC()const { return C; }

	void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	BOOL HitTest(float x, float y);
	Bounds bounds();
private:

	void copy(const Obj& x) {
		copy(*(Triangle*)&x);;
	};
	void copy(const Triangle& other);
	Vec A;
	Vec B;
	Vec C;
};

