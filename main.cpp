#include <iostream>
#include "./include/interpreter.hpp"

int main()
{
	Interpreter interpreter;
	interpreter.run("3 + 4 / 2 * 1 - 5  * 2 * 3");
	return 0;
}