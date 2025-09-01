#include <iostream>
#include "./include/interpreter.hpp"

int main(int argc, char* args[])
{
	Interpreter interpreter;
	interpreter.run(argc, args);
	return 0;
}