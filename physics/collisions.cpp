#include "collisions.h"

Collisions::Collisions()
{

}

void Collisions::sphere_to_sphere(Sphere obj1, Sphere obj2){

}


double Collisions::distance(double x1,double x2, double y1, double y2){
 double xdist = x1-x2;
 double ydist = y1-y2;

 return pow(xdist*xdist + ydist*ydist,.5);
}
