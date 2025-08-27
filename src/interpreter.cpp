#include <iostream>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"


void Interpreter::run()
{
	ContainerVec* cons = tokenizer.tokenize("12121 + 59 / 6");
	ContainerVec* parsed_cons = parser.parse(cons);
	print_containers(parsed_cons);
	delete cons;
	delete parsed_cons;

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
