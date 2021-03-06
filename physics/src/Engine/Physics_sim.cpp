#include "Physics_sim.h"

Vec runge_kutta(const Vec& x, force f, const float& t, const float& h, const size_t& n) {
    Vec k1, k2, k3, k4;
    Vec y = Vec(x.x, x.y);

    for (size_t i = 0; i < n; i++) {
        k1 = h * (f(y, t));
        k2 = h * f(y + (0.5 * k1), t + 0.5 * h);
        k3 = h * f(y + (0.5 * k2), t + 0.5 * h);
        k4 = h * f(y + (k3), t + h);
        y = y + (0.1666667) * (k1 + (2 * k2) + (2 * k3) + k4);
    }
    return y;
}
Vec earth_grav(Vec x, const float& t) {
    return Vec(0, 9.8);
}
Vec force_field(Vec x, const float& t) {
    return Vec(2*cos(x.y),2*sin(4*x.y));
}
void apply_force_field(Obj& x, force f, Vec bounds) {
    Vec temp = runge_kutta(x.get_pos(), f, .1, 1, 1);
    Bounds check(x.get_pos(), temp);
    if ((check.lowerR.x >= 0 && check.upperL.x < bounds.x) && (check.lowerR.y >= 0 && check.upperL.y < bounds.y))
        x.set_pos(temp);
}

void grav(Obj& x, force f, Vec bounds) {
    Vec pos = runge_kutta(x.get_pos(), f, 1, 1, 1);

    if((x.bounds().lowerR.x  >= 0 && x.bounds().upperL.x  < bounds.x) && (x.bounds().lowerR.y >= 0 && x.bounds().upperL.y < bounds.y))
         x.set_pos(pos);
}
/*Member Functions:*/
Engine::Engine(float x, float y){
    time = 0.0;
    selection = objs.end();
    this->xBounds = x;
    this->yBounds = y;
}

Engine::~Engine() {
    objs.clear();
    time = 0.0;
}

void Engine::add_obj(Obj& obj){
    if (obj.get_type() == TYPE::SPHERE) {
        selection = objs.insert(
            objs.end(),
            std::shared_ptr<Sphere>(new Sphere(obj)));
    }

    if (obj.get_type() == TYPE::PLANE) {
        selection = objs.insert(
            objs.end(),
            std::shared_ptr<Plane>(new Plane(obj)));
    }

    if (obj.get_type() == TYPE::TRIANGLE) {
        selection = objs.insert(
            objs.end(),
            std::shared_ptr<Triangle>(new Triangle(obj)));
    }
}


void Engine::step(){
    collision();
    for (auto i = objs.rbegin(); i != objs.rend(); ++i) {
        apply(*(*i), CONST_ACC, time);
    }
}



void Engine::render(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush) {
    
    for (auto i = objs.rbegin(); i != objs.rend(); ++i) {
        (*i)->Draw(pRT, pBrush);
    }

}
void Engine::apply(Obj& x, FUNC f, float t) {

    switch (f)
    {
    case CONST_ACC:
       // grav(x, earth_grav,Vec(xBounds,yBounds));
        apply_force_field(x, force_field, Vec(xBounds, yBounds));
        break;
    case ACC:
        break;
    case VEL:
        break;
    default:
        break;
    }
}

BOOL Engine::hit_test(float x, float y) {
    for (auto i = objs.rbegin(); i != objs.rend(); ++i) {
        if ((*i)->HitTest(x, y)) {
            selection = (++i).base();
            return TRUE;
        }
    }
    return FALSE;
}

std::shared_ptr<Obj> Engine::Selection(){
    if (selection == objs.end()) {
        return nullptr;
    }
    else {
        return(*selection);
    }
}

void Engine::collision() {
    for (auto obj1 = objs.begin(); obj1 != objs.end(); obj1 = std::next(obj1,1)) {
        for (auto obj2 = std::next(obj1,1); obj2 != objs.end(); obj2 = std::next(obj2,1)){
            Obj* x = obj1->get();
            Obj* y = obj2->get();

            if (collisions.iscolliding(*x, *y)) {
                MessageBox(NULL, L"colliding", L"colliding", MB_OK | MB_ICONQUESTION);
            }
        }
    }
}