#include <iostream>
#include <string>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run(int argc, char* args[])
{
	if (argc < 1)
	{
		interpretREPL();
		return;
	}

}

void Interpreter::interpretREPL()
{
	std::cout << "Running mathz in REPL mode." << std::endl;

	while (true)
	{
		std::string line;

		std::cout << ">>> ";
		std::getline(std::cin, line);

		if (line == "quit") {break;}
		
		interpretString(line);
		printResult();
	}
}

void Interpreter::printResult()
{
	Container result = evaluator.yield();
}