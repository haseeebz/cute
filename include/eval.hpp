#include <iostream>
#include <vector>
#include "container.hpp"

#pragma once


class Evaluator
{
	std::vector<Container>result_stack;

	void evalExpr(Container& op, Container& c1, Container& c2);

	Container add(Container& c1, Container& c2);
	Container subtract(Container& c1, Container& c2);
	Container multiply(Container& c1, Container& c2);
	Container divide(Container& c1, Container& c2);
	Container power(Container& c1, Container& c2);
	

	public:

	void evaluate(ContainerVec* containers);
	int yield();
};