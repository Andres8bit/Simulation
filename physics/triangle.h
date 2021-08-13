#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "obj.h"

class Triangle: public Obj{
public:
    Triangle(Vec apos = Vec(), Vec bpos = Vec(), Vec cpos = Vec())
                {this->a = apos; this->b = bpos; this->c = cpos;}
    ~Triangle(){*this = Triangle();}

private:
    Vec a;
    Vec b;
    Vec c;
};

#endif // TRIANGLE_H
