#include <iostream>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run()
{
	std::string str = "4- 5  *  5 -12";

	ContainerVec* cons = tokenizer.tokenize(str);
	ContainerVec* parsed_cons = parser.parse(cons);
	
	evaluator.evaluate(parsed_cons);
	int result = evaluator.yield();

	std::cout << str << std::endl;
	print_containers(cons);
	print_containers(parsed_cons);
	std::cout << "Result: " << result << std::endl;

	delete cons;
	delete parsed_cons;
}
