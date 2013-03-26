#ifndef PLAYER_CPP_AI_EXCEPTION_H
#define PLAYER_CPP_AI_EXCEPTION_H

#include <exception>

using std::exception;

class PlayerCppAIException : exception
{
public:
	PlayerCppAIException() : exception(), msg("")
	{
	
	}
	PlayerCppAIException(const char* message) : exception(), msg(message)
	{
	
	}

protected:
	virtual const char* what() const throw() {
		return msg;
	}
	
	const char* msg;
};

#endif
