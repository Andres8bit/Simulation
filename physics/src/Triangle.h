#pragma once
#include "Obj.h"
#include<wrl.h>

class Triangle :public Obj{
public:
	Triangle(const Vec& a, const Vec& b, const Vec& c);
	Triangle(const Triangle& other);
	Triangle& operator=(const Triangle& other);
	
	std::vector<Vec> vertices()const;
	Vec get_pos()const;
	Vec center_mass()const;
	void set_pos(const Vec pos);
	D2D1_POINT_2F getA()const { return A; }
	D2D1_POINT_2F getB()const { return B; }
	D2D1_POINT_2F getC()const { return C; }

	void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	BOOL HitTest(float x, float y);
	Bounds bounds();
private:
	void copy(const Obj& x) {
		copy(*(Triangle*)&x);;
	};
	void copy(const Triangle& other);
	D2D1_POINT_2F A;
	D2D1_POINT_2F B;
	D2D1_POINT_2F C;
};

