#include "Obj.h"
 Obj::Obj(){
	this->color = D2D1::ColorF(D2D1::ColorF::Black);
	this->mass = 0.0;
	 this->acc = Vec();
	this->vel = Vec();
	this->angle_of_rotation = 0;
};