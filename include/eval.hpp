#include <iostream>
#include <vector>
#include "container.hpp"

#pragma once


class Evaluator
{
	std::vector<Container>result_stack;

	void eval_expr(Container& op, Container& c1, Container& c2);
	public:

	void evaluate(ContainerVec* containers);
	int yield();
};