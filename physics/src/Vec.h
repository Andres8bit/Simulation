#pragma once
struct Vec
{

    double x;
    double y;

    Vec(double x = 0, double y = 0)
    {
        this->x = x; this->y = y;
    }
    Vec(const Vec& val)
           {this->x = val.x; this->y = val.y;}

    double dot(const Vec& y) 
           {return this->x * y.x + this->y * y.y;}
    Vec scalar_mutl(const double& C) 
           { return Vec(this->x *= C, this->y *= C); }

    friend
        Vec operator+(const Vec& x, const Vec& y);
};


Vec operator+(const Vec& x, const Vec& y) {
    return Vec(x.x + y.x, x.y + y.y);
}