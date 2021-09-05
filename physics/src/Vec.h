#pragma once
#include<math.h>
struct Vec {
	double x, y;
    Vec(double x = 0, double y = 0){ this->x = x; this->y = y; }
    Vec(const Vec& val) { x = val.x; y = val.y; }
    Vec& operator=(Vec const other) {
        if (this == &other)
            return *this;
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    
    friend
        double dot(const Vec& x, const Vec& y); 
    friend
        Vec operator+(const Vec& x, const Vec& y);
    friend
        Vec operator*(const double& c, const Vec& y);    
    friend
        Vec operator-(const Vec& x, const Vec& y);
    friend
        Vec operator/(const Vec& y,const double& x );
    friend
        double magnitude(const Vec& x);
};
