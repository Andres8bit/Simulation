#pragma once
#include "Obj.h"

typedef Vec(*force)(Vec, const double&);
enum FUNC {CONST_ACC,ACC,VEL};
/*Forces:*/
// Earth Graviational force acting on acceleration.
class force {
private:
    Vec runge_kutta(const Vec& x,Vec f, const double& t, const double& h, const size_t& n);
    Vec earth_grav(Vec x, const double& t) {
        return Vec(0, 9.8);
    }
    void grav(Obj& x, force f, double& t) {
        x.set_acc(runge_kutta(x.get_acc(), f, t, t / 10, 10));
    }
public:

    void apply(Obj& x, FUNC f, double t) {

        switch (f)
        {
        case CONST_ACC:
            break;
        case ACC:
            break;
        case VEL:
            break;
        default:
            break;
        }
    }

};
