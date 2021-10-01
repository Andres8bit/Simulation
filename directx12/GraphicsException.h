#pragma once
#include"Exception.h"

class GraphicsException : public Exception {

public:
	GraphicsException(ErrorType errType) {
		err_type = errType;
	}

	const char* what()throw() {
		return err_type == ErrorType::FATAL_ERROR ?
			"Fatal Error: Graphics" : "Lost Device: Graphics";
	}

};