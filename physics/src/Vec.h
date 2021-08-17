#pragma once
struct Vec
{
    typedef Vec(*force)(const Vec&, const double&);
    double x;
    double y;

    Vec(double x = 0, double y = 0)
    {
        this->x = x; this->y = y;
    }
    Vec(const Vec& val)
           {this->x = val.x; this->y = val.y;}

    double dot(const Vec& y) 
           { return this->x * y.x + this->y * y.y;}
    Vec scalar_mutl(const double& C) 
           { return Vec(this->x *= C, this->y *= C);}

    Vec add(const Vec& y) 
           { return Vec(this->x + y.x, this->y + y.y);}

    // solves ODE where:
   //			f = dx/dt -> f(x,t) 
   //			h = step_size 
   //			n = number of steps
   //			x = Vec -> init vector. 
   //			returns approximate solution as vec
    Vec rk4(const Vec& x, const force f, const double& t, const double& h, const size_t& n) {
        Vec k1, k2, k3, k4, sum;
        Vec y = x;

        for (int i = 0; i < n; i++) {
            k1 = f(y, t).scalar_mutl(h);
            k2 = f(y.add(k1.scalar_mutl(0.5)), t + 0.5 * h).scalar_mutl(h);
            k3 = f(y.add(k2.scalar_mutl(0.5)), t + 0.5 * h).scalar_mutl(h);
            k4 = f(y.add(k3), t + h).scalar_mutl(h);
            sum = k1.add(k2.scalar_mutl(2));
            sum = sum.add(k4.add(k3.scalar_mutl(2)));
            sum = sum.scalar_mutl(1 / 6);
            y = y.add(sum);
        }
        return y;
    }
};