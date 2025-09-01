#include <iostream>
#include "./include/interpreter.hpp"

int main()
{
	Interpreter interpreter;
	interpreter.run("2000 + 1 - 19.9999");
	return 0;
}