#include "Force.h"


// solves ODE where:
//			f = dx/dt -> f(x,t) 
//			h = step_size 
//          t = time step
//			n = number of steps
//			x = Vec -> init vector. 
//			returns approximate solution as vec
Vec force::runge_kutta(const Vec& x, Vec f, const double& t, const double& h, const size_t& n) {
    Vec k1, k2, k3, k4;
    Vec y = Vec(x.x, x.y);

    for (size_t i = 0; i < n; i++) {
        k1 = h * (f(y, t));
        k2 = h * f(y + (0.5 * k1), t + 0.5 * h);
        k3 = h * f(y + (0.5 * k2), t + 0.5 * h);
        k4 = h * f(y + (k3), t + h);
        y = y + 1 / 6 * (k1 + (2 * k2) + (2 * k3) + k4);
    }
    return y;
}
