#include <iostream>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run()
{
	ContainerVec* cons = tokenizer.tokenize("1+ 5 / 6");
	print_containers(cons);
	delete cons;
	
	ContainerVec containers;
	containers.push_back(Container(3));
	containers.push_back(Container(4));
	containers.push_back(Container(BinaryOpType::Mul));
	containers.push_back(Container(6));
	containers.push_back(Container(BinaryOpType::Div));
	containers.push_back(Container(2));
	containers.push_back(Container(BinaryOpType::Sub));

	evaluator.evaluate(&containers);
	int result = evaluator.yield();

	std::cout << "Result: " << result << std::endl;
}
