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
			parsed_containers->push_back(current);
			continue;
		}

		if (current.type == ContainerType::BinaryOp)
		{

			while (op_containers_stack.size() > 0)
			{
				Container prev_op = op_containers_stack.back();

				bool precedes = precedence(current.value.op, prev_op.value.op);

				if (precedes)
				{
					parsed_containers->push_back(prev_op);
					op_containers_stack.pop_back();
				}
				else
				{
					break;
				}
			}

			op_containers_stack.push_back(current);

			continue;
		}

		if (current.type == ContainerType::Paran)
		{
			if (current.value.paran == ParanType::Left)
			{
				op_containers_stack.push_back(current);
				continue;
			}

			if (current.value.paran == ParanType::Right)
			{
				Container top = op_containers_stack.back();

				while (top.type != ContainerType::Paran && top.value.paran != ParanType::Left)
				{
					parsed_containers->push_back(top);
					op_containers_stack.pop_back();
					top = op_containers_stack.back();
				}
				op_containers_stack.pop_back(); // removing the left paran

			}

		}

	}

	while (op_containers_stack.size() > 0)
	{
		parsed_containers->push_back(op_containers_stack.back());
		op_containers_stack.pop_back();
	}

	return parsed_containers;
}

bool Parser::precedence(BinaryOpType op1, BinaryOpType op2)
{
	if (op1 > op2) 
	{
		return false;
	}
	return true;
}
