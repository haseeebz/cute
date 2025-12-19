#include <iostream>
#include <string>
#include <vector>

#pragma once

// Global Error variable for ease

namespace CtError
{

	enum class ErrorType
	{
		SyntaxError = 0,
		NameError   = 1,
		TypeError   = 2,
		CompilerError = 3
	};

	struct Error
	{
		std::string name;
		std::string message;
	};

	inline Error error;

	inline bool errorRaised = false;

	inline void raise(ErrorType type, std::string msg)
	{
		static std::vector<std::string> error_name = {
			"SyntaxError",
			"NameError",
			"TypeError"
			"CompilerError"
		};

		error.name = error_name[int(type)];
		error.message = msg;

		// this is temporary, will add proper error raising instead.

		std::cout << "[ " << error.name << " ] " << error.message << std::endl;
		exit(1);
	}

}