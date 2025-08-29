#include <iostream>
#include "./include/interpreter.hpp"

int main()
{
	Interpreter interpreter;
	interpreter.run("(10 + (20 - 10) ) * (10 - 5) - 10 / 5");
	return 0;
}