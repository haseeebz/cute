#include "../include/container.hpp"
#include "../include/parser.hpp"


ContainerVec* Parser::parse(ContainerVec* containers)
{
	tokenized_containers = containers;
	parsed_containers = new ContainerVec;

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
			if (!op_containers_stack->empty())
			{
				Container prev_op = op_containers_stack->back();

				bool precedes = precedence(current.value.op, prev_op.value.op);

				if (precedes)
				{
					parsed_containers->push_back(prev_op);
					op_containers_stack->pop_back();
				}
			}
			parsed_containers->push_back(current);
			continue;
		}
	}

	while (!op_containers_stack->empty())
	{
		parsed_containers->push_back(op_containers_stack->back());
		op_containers_stack->pop_back();
	}

	return parsed_containers;
	
}

bool Parser::precedence(BinaryOpType op1, BinaryOpType op2)
{
	if (op2 >= op1) 
	{
		return false;
	}
	return true;
}
