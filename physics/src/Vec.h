#pragma once
#include<math.h>


struct Vec {
	double x, y;
    Vec(double x = 0, double y = 0){ this->x = x; this->y = y; }
    Vec(const Vec& val) { x = val.x; y = val.y; }
   
    Vec& operator=(Vec const other) {
        if (this == &other)
            return *this;
        copy(other);
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
    friend
        double distance(const Vec& x, const Vec& y);
    friend
        Vec inverse(const Vec& x);
    friend
        Vec polar(const double& angle, const double& radius);
    friend
        double angle(const Vec& x);
    friend
        Vec norm(const Vec& x);
    friend
        double lenSqrd(const Vec& x);
    friend
        Vec perp(const Vec& x);
    friend
        Vec translate(const Vec& x, const double& tx, const double& ty);
    friend
        Vec rotate(const Vec& x, const float& rad);
    friend
        Vec shear(const Vec& x, const float& sx, const float& sy);
    friend
        Vec scale(const Vec& x, const double& sx, const double& sy);

private:
        void copy(const Vec& other){
            this->x = other.x;
            this->y = other.y;
        }
};
