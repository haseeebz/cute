#include <iostream>
#include "./include/interpreter.hpp"

int main()
{
	Interpreter interpreter;
	interpreter.run("(10 / 4) * 9.9 - 90");
	return 0;
}