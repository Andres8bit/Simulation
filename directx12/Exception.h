#pragma once
#include<iostream>
enum class ErrorType{FATAL_ERROR,GRAPHICS_ERROR,INPUT_ERROR,LOST_DEVICE};

class Exception : public std::exception {
protected:
	ErrorType err_type;

public:
	virtual const char* what()throw() = 0;
	

};