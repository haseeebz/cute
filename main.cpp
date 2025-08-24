#include <iostream>
#include "./include/eval.hpp"
#include "./include/container.hpp"


int main()
{
	Evaluator eval;

	ContainerVec containers;
	containers.push_back(Container(10));
	containers.push_back(Container(10));
	containers.push_back(Container(BinaryOpType::Add));

	eval.evaluate(&containers);
	int result = eval.yield();

	std::cout << "Result: " << result << std::endl;
}