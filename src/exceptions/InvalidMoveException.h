//
// Created by Lindsey on 9/26/2024.
//

#ifndef INVALIDMOVEEXCEPTION_H
#define INVALIDMOVEEXCEPTION_H

#include <exception>
#include <string>


namespace Exceptions
{
class InvalidMoveException : public std::exception{
public:
	explicit InvalidMoveException(const std::string& message);

	virtual const char* what() const noexcept override;

private:
	std::string errorMessage;

};

}

#endif //INVALIDMOVEEXCEPTION_H
