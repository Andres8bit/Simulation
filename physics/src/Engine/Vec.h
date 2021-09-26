#pragma once
#include<math.h>


struct Vec {
	float x, y;
    Vec(float x = 0, float y = 0){ this->x = x; this->y = y; }
    Vec(const Vec& val) { x = val.x; y = val.y; }
   
    Vec& operator=(Vec other) {
        if (this == &other)
            return *this;
        copy(other);
        return *this;
    }
    
    friend
        float dot(const Vec& x, const Vec& y); 
    friend
        Vec operator+(const Vec& x, const Vec& y);
    friend
        Vec operator*(const float& c, const Vec& y);    
    friend
        Vec operator-(const Vec& x, const Vec& y);
    friend
        Vec operator/(const Vec& y,const float& x );
    friend
        float magnitude(const Vec& x);
    friend
        float distance(const Vec& x, const Vec& y);
    friend
        Vec inverse(const Vec& x);
    friend
        Vec polar(const float& angle, const float& radius);
    friend
        float angle(const Vec& x);
    friend
        Vec norm(const Vec& x);
    friend
        float lenSqrd(const Vec& x);
    friend
        Vec perp(const Vec& x);
    friend
        Vec translate(const Vec& x, const float& tx, const float& ty);
    friend
        Vec rotate(const Vec& x, const float& rad);
    friend
        Vec shear(const Vec& x, const float& sx, const float& sy);
    friend
        Vec scale(const Vec& x, const float& sx, const float& sy);

private:
        void copy(const Vec& other){
            this->x = other.x;
            this->y = other.y;
        }
};
