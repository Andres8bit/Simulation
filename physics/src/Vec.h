#pragma once

struct Vec
{

    double x;
    double y;

    Vec(double x = 0, double y = 0)
           {this->x = x; this->y = y;}
    Vec(const Vec& val)
           {this->x = val.x; this->y = val.y;}
  
    double dot(const Vec& y) 
           { return this->x * y.x + this->y * y.y;}
    Vec scalar_mutl(const double& C) 
           { return Vec(this->x *= C, this->y *= C);}
    Vec add(const Vec& y) 
           { return Vec(this->x + y.x, this->y + y.y);}

    friend
        Vec operator+(const Vec& x, const Vec& y);
    friend
        Vec operator*(const double& c,const Vec& y);
    friend
        Vec earth_grav(Vec x, const double& t);
};

typedef Vec(force)(Vec, const double&);





// solves ODE where:
//			f = dx/dt -> f(x,t) 
//			h = step_size 
// 
//			n = number of steps
//			x = Vec -> init vector. 
//			returns approximate solution as vec
Vec rk4(const Vec& x, force f, const double& t, const double& h, const size_t& n) {
    Vec k1, k2, k3, k4, sum;
    Vec y = Vec(x.x, x.y);

    for (int i = 0; i < n; i++) {
        k1 = h * (f(y, t));
        k2 = h * f(y + (0.5 * k1), t + 0.5 * h);
        k3 = h * f(y + (0.5 * k2), t + 0.5 * h);
        k4 = h * f(y + (k3), t + h);
        y = y + 1 / 6 * (k1 + (2 * k2) + (2 * k3) + k4);
    }
    return y;
}

