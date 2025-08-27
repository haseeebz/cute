#include <iostream>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run()
{
	ContainerVec* cons = tokenizer.tokenize("2 + 2 + 2 * 2");
	ContainerVec* parsed_cons = parser.parse(cons);
	
	evaluator.evaluate(parsed_cons);
	int result = evaluator.yield();
	std::cout << "Result: " << result << std::endl;

	delete cons;
	delete parsed_cons;
}
