#ifndef OBJ_H
#define OBJ_H

enum TYPE{SPHERE,TRIANGLE,PLANE};
struct Vec{
    double x;
    double y;
};

class Obj{
public:
    Obj(double objmass = 0.01)
    {this->mass = objmass;this->vel = Vec(); this->acc = Vec();}
    ~Obj(){this->mass = 0.0;}

    double get_mass(){return this->mass;}
    void set_mass(double val){this->mass = val;}
    void set_vel(Vec val){this->vel = val;}
    void set_acc(Vec val){this->acc = val;}
private:
    double mass;
    Vec vel;
    Vec acc;
};

#endif // OBJ_H
