#include <iostream>
#include "./include/interpreter.hpp"

int main(int argc, char* argv[])
{
	Interpreter interpreter;
	interpreter.run(argc, argv);
	return 0;
}