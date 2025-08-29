#include "../include/container.hpp"
#include "../include/tokenizer.hpp"
#include "../include/parser.hpp"


ContainerVec* Parser::parse(ContainerVec* containers)
{
	tokenized_containers = containers;
	parsed_containers = new ContainerVec;
	op_containers_stack.clear();

	Container current;

	for (int i = 0; i < tokenized_containers->size(); i++)
	{
		current = tokenized_containers->at(i);

		if (current.type == ContainerType::Int)
		{
			parse_int(current);
			continue;
		}

		if (current.type == ContainerType::BinaryOp)
		{
			parse_binaryOp(current);
			continue;
		}

		if (current.type == ContainerType::Paran)
		{
			parse_paran(current);
			continue;
		}

	}

	while (op_containers_stack.size() > 0)
	{
		parsed_containers->push_back(op_containers_stack.back());
		op_containers_stack.pop_back();
	}

	return parsed_containers;
}


void Parser::parse_int(Container& current)
{
	parsed_containers->push_back(current);
}


void Parser::parse_binaryOp(Container& current)
{

	while (op_containers_stack.size() > 0)
	{

		Container prev_op = op_containers_stack.back();

		if (prev_op.type == ContainerType::Paran) {break;}

		bool precedes = precedence(current.value.op, prev_op.value.op);

		if (precedes)
		{
			parsed_containers->push_back(prev_op);
			op_containers_stack.pop_back();
		}
		else {
			break;
		}

	}

	op_containers_stack.push_back(current);

}


void Parser::parse_paran(Container& current)
{
	if (current.value.paran == ParanType::Left)
	{
		op_containers_stack.push_back(current);
		return;
	}

	if (current.value.paran == ParanType::Right)
	{
		Container top = op_containers_stack.back();

		while (true)
		{
			if (top.type == ContainerType::Paran)
			{
				if (top.value.paran != ParanType::Left) {continue;}

				op_containers_stack.pop_back();
				break;
			}

			parsed_containers->push_back(top);
			op_containers_stack.pop_back();
			top = op_containers_stack.back();
		}
	}
}


bool Parser::precedence(BinaryOpType op1, BinaryOpType op2)
{
	if (op1 > op2) 
	{
		return false;
	}
	return true;
}
