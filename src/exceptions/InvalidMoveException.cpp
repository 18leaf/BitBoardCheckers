//
// Created by Lindsey on 9/26/2024.
//

#include "InvalidMoveException.h"

using namespace Exceptions;

InvalidMoveException::InvalidMoveException(const std::string &message)
	: errorMessage(message){
}

const char* InvalidMoveException::what() const noexcept {
	return errorMessage.c_str();
}
