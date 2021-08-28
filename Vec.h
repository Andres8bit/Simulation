#pragma once
struct Vec {
	double x, y;
    Vec(double x = 0, double y = 0){ this->x = x; this->y = y; }
    Vec(const Vec& val) { x = val.x; y = val.y; }
    double dot(const Vec& y){ return x * y.x + this->y * y.y;}
    friend
        Vec operator+(const Vec& x, const Vec& y);
    friend
        Vec operator*(const double& c, const Vec& y);       
};