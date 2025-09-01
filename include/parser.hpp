#include "container.hpp"

#pragma once

class Parser
{
	ContainerVec* parsed_containers;
	ContainerVec* tokenized_containers;
	ContainerVec op_containers_stack;

	public:

	ContainerVec* parse(ContainerVec* containers);
	void parseDigit(Container& current);
	void parseBinaryOp(Container& current);
	void parseParan(Container& current);
	bool precedence(BinaryOpType op1, BinaryOpType op2);
};