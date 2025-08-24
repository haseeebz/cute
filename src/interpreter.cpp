#include <iostream>
#include <vector>
#include "../include/container.hpp"
#include "../include/interpreter.hpp"



void Interpreter::run()
{
	ContainerVec containers;
	containers.push_back(Container(10));
	containers.push_back(Container(5));
	containers.push_back(Container(5));
	containers.push_back(Container(BinaryOpType::Sub));
	containers.push_back(Container(BinaryOpType::Sub));
	containers.push_back(Container(2));
	containers.push_back(Container(BinaryOpType::Mul));

	eval.evaluate(&containers);
	int result = eval.yield();

	std::cout << "Result: " << result << std::endl;
}
