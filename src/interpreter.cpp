#include <iostream>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run(std::string expr)
{
	ContainerVec* cons = tokenizer.tokenize(expr);
	ContainerVec* parsed_cons = parser.parse(cons);
	
	evaluator.evaluate(parsed_cons);
	int result = evaluator.yield();

	std::cout << expr << std::endl;
	print_containers(cons);
	print_containers(parsed_cons);
	std::cout << "Result: " << result << std::endl;

	delete cons;
	delete parsed_cons;
}
