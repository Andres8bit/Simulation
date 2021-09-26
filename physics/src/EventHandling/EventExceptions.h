#pragma once
#include<iostream>
#include"Utils.h"
class EventExceptions : public std::exception {
private:
	ErrorType type;
public:
	EventExceptions(ErrorType errType) {
		type = errType;
	}

	const char* what()throw() {
		return type == ErrorType::FATAL_ERROR ?
			"Fatal Error: Event Handling" : "Lost Device: Event Handling";
	}
};
