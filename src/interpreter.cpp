#include <iostream>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run(std::string expr)
{
	std::cout << expr << std::endl;

	ContainerVec* cons = tokenizer.tokenize(expr);
	print_containers(cons);

	ContainerVec* parsed_cons = parser.parse(cons);
	print_containers(parsed_cons);
	
	evaluator.evaluate(parsed_cons);
	int result = evaluator.yield();
	
	std::cout << "Result: " << result << std::endl;

	delete cons;
	delete parsed_cons;
}
