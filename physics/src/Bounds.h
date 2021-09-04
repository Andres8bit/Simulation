#pragma once
#include "Vec.h"
struct Bounds {
	Vec upperL;
	Vec lowerR;

	Bounds(Vec top = Vec(), Vec bottom= Vec()) 
	{ this->upperL = top; this->upperL = bottom; }

    Bounds& operator=(Bounds const other) {
        if (this == &other)
            return *this;
        this->upperL = other.upperL;
        this->lowerR = other.lowerR;
        return *this;
    }

    bool hitTest(Bounds& x, Bounds& y) {
    
    }
};