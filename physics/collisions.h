#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "sphere.h"
#include "triangle.h"
#include "plane.h"
#include<math.h>
class Collisions{
public:
    Collisions();
    void sphere_to_sphere(Sphere obj1, Sphere obj2);
    void sphere_to_triangle(Sphere sp, Triangle tri);
    void sphere_to_plane(Sphere sp, Plane pl);
private:
    double distance(double x1,double x2, double y1, double y2);
    double linear_force(const Obj& obj1,const Obj& obj2);
    double torgue(const Sphere& obj1, const Sphere& obj2);
};

#endif // COLLISIONS_H
