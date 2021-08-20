#include "Obj.h"

Obj::Obj() {
	this->set_mass(0);
}

Obj::~Obj() {
	this->set_acc(Vec(0, 0));
	this->set_mass(0);
	this->set_vel(Vec(0, 0));
}