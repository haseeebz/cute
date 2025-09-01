#include <iostream>
#include "./include/interpreter.hpp"

int main()
{
	Interpreter interpreter;
	interpreter.run("2000 + 1 - 1999");
	return 0;
}