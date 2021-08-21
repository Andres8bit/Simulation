#include "Obj.h"
Obj::Obj() {
	this->set_mass(0);
}
Obj::Obj(const Obj& x){
	copy(x);
}

Obj::~Obj() {
	this->set_acc(Vec(0, 0));
	this->set_mass(0);
	this->set_vel(Vec(0, 0));
}

void Obj::copy(const Obj& x) {
	this->mass = x.get_mass();
	this->acc = x.get_acc();
	this->vel = x.get_vel();
	this->t = x.get_type();
}