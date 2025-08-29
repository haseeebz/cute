#include <iostream>
#include "./include/interpreter.hpp"

int main()
{
	Interpreter interpreter;
	interpreter.run(" (10 + 10 * ( 4 - 5 ) -10 ) + 45");
	return 0;
}