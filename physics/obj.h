#ifndef OBJ_H
#define OBJ_H

enum TYPE{SPHERE,TRIANGLE,PLANE};
struct Vec{
    Vec(double x=0, double y=0)
        {this->x = x; this->y = y;}
    Vec(const Vec& val)
        {this->x = val.x; this->y = val.y;}
    double x;
    double y;
};

class Obj{
public:
    Obj(double objmass = 0.01)
    {this->mass = objmass;this->vel = Vec(); this->acc = Vec();}
    ~Obj(){this->mass = 0.0;}

    //getters:
    double get_mass(){return this->mass;}
    TYPE get_type(){return this->t;}
    Vec get_vel(){return this->vel;}
    Vec get_acc(){return this->acc;}

    //setter:
    void set_mass(double val){this->mass = val;}
    void set_vel(Vec val){this->vel = val;}
    void set_acc(Vec val){this->acc = val;}

    void set_type(TYPE val){this->t = val;}
private:
    double mass;
    Vec vel;
    Vec acc;
    TYPE t;
};

#endif // OBJ_H
