#pragma once
#include "obj.h"

class Plane : public Obj {
public:
    Plane(Vec upperR = Vec(), Vec upperL = Vec(), Vec lowerR = Vec(), Vec lowerL = Vec())
    {
        this->ur = upperR; this->ul = upperL; this->lr = lowerR; this->ll = lowerL; this->set_type(TYPE::PLANE);
    }
    ~Plane() { this->ur = this->ul = this->lr = this->ll = Vec(); }

    void step_position();
    void step_orientation();

private:
    Vec ur;
    Vec ul;
    Vec lr;
    Vec ll;
};
