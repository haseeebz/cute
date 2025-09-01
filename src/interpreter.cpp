#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run(int argc, char* argv[])
{

	if (argc <= 1)
	{
		interpretREPL();
		return;
	}

}

void Interpreter::interpretREPL()
{
	std::cout << "Running mathz in REPL mode." << std::endl;
	std::string line;

	while (true)
	{
		
		std::cout << ">>> ";
		std::getline(std::cin, line);

		if (line == "quit") {break;}

		interpretString(line);
		printResult();
	}
}


void Interpreter::interpretString(std::string expr)
{
	ContainerVec* cons = tokenizer.tokenize(expr);
	ContainerVec* parsed_cons = parser.parse(cons);
	evaluator.evaluate(parsed_cons);
	delete cons;
	delete parsed_cons;
}


void Interpreter::printResult()
{
	Container result = evaluator.yield();
	print_container_value(result);
	std::cout << std::endl;
}
