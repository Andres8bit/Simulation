#pragma once
#include<iostream>
#include"Utils.h"
class GraphicsException : public std::exception {
private:
	ErrorType type;
public:
	GraphicsException(ErrorType errType) {
		type = errType;
	}

	const char* what()throw(){
		return type == ErrorType::FATAL_ERROR ?
			   "Fatal Error: Graphics" : "Lost Device: Graphics";
	}
};

