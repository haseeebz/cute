#include "container.hpp"

#pragma once

class Parser
{
	ContainerVec* parsed_containers;
	ContainerVec* tokenized_containers;
	ContainerVec op_containers_stack;

	public:

	ContainerVec* parse(ContainerVec* containers);
	void parse_int(Container& current);
	void parse_binaryOp(Container& current);
	void parse_paran(Container& current);
	bool precedence(BinaryOpType op1, BinaryOpType op2);
};