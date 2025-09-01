#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run(int argc, char* argv[])
{
	std::cout << "argc = " << argc << "\n";
    for (int i = 0; i < argc; ++i) {
        std::cout << "argv[" << i << "] = " << argv[i] << "\n";
    }

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
		std::cout << line << std::endl;
		interpretString(line);
		printResult();
	}
}


void Interpreter::interpretString(std::string expr)
{
	ContainerVec* cons = tokenizer.tokenize("2+ 2");
	ContainerVec* parsed_cons = parser.parse(cons);
	print_containers(cons);
	print_containers(parsed_cons);
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
