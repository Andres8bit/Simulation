#include "Physics_sim.h"

Vec runge_kutta(const Vec& x, force f, const double& t, const double& h, const size_t& n) {
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
Vec earth_grav(Vec x, const double& t) {
    return Vec(0, 9.8);
}

void grav(Obj& x, force f, double& t) {
    Vec pos = x.get_pos() + runge_kutta(x.get_acc(), f, t, t / 10, 10);
    x.set_pos(pos);
}
/*Member Functions:*/
Engine::Engine(){
    time = 0.0;
}

Engine::~Engine() {
    objs.clear();
    time = 0.0;
}

void Engine::add_obj(Sphere& obj){
    MessageBox(NULL, L"adding", L"engine", NULL);
    objs.insert(
        objs.end(),
        std::shared_ptr<Sphere>(new Sphere(obj)));
    
}


void Engine::step(){

    for (auto i = objs.rbegin(); i != objs.rend(); ++i) {
       // apply(*(*i), CONST_ACC, time);
        apply(*(*i), CONST_ACC, time);
    }
    
}



void Engine::render(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush) {
    pRT->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
    for (auto i = objs.rbegin(); i != objs.rend(); ++i) {
        // apply(*(*i), CONST_ACC, time);
        (*i)->Draw(pRT, pBrush);
    }

}
void Engine::apply(Sphere& x, FUNC f, double t) {

    switch (f)
    {
    case CONST_ACC:
        grav(x, earth_grav, time);
        break;
    case ACC:
        break;
    case VEL:
        break;
    default:
        break;
    }
}
