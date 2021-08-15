#pragma once
#include "obj.h"

class Triangle : public Obj {
public:
    Triangle(Vec apos = Vec(), Vec bpos = Vec(), Vec cpos = Vec())
    {
        this->a = apos; this->b = bpos; this->c = cpos; this->set_type(TYPE::TRIANGLE);
    }
    ~Triangle() { this->a = this->b = this->c = Vec(); }

private:
    Vec a;
    Vec b;
    Vec c;
};