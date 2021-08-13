#ifndef PLANE_H
#define PLANE_H
#include "obj.h"

class Plane: public Obj{
public:
    Plane(Vec upperR = Vec(), Vec upperL = Vec(), Vec lowerR = Vec(), Vec lowerL = Vec())
          {this->ur = upperR; this->ul = upperL; this->lr = lowerR; this->ll = lowerL; this->set_type( TYPE::PLANE);}
    ~Plane(){*this = Plane();}

private:
    Vec ur;
    Vec ul;
    Vec lr;
    Vec ll;
};

#endif // PLANE_H
