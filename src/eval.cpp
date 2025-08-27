#include <iostream>
#include <vector>
#include "../include/container.hpp"
#include "../include/eval.hpp"


void Evaluator::eval_expr(Container& op, Container& c1, Container& c2)
{

	int num;

	switch (op.value.op) 
	{
		case BinaryOpType::Add : num = c1.value.i + c2.value.i; break;
		case BinaryOpType::Sub : num = c1.value.i - c2.value.i; break;
		case BinaryOpType::Mul : num = c1.value.i * c2.value.i; break;
		case BinaryOpType::Div : num = c1.value.i / c2.value.i; break;
		default: return;
	}

	Container result(num);
	result_stack.push_back(result);
}


void Evaluator::evaluate(ContainerVec* containers)
{
	for (int i = 0; i < containers->size(); i++)
	{
		Container con = containers->at(i);

		if (con.type == ContainerType::Int)
		{
			result_stack.push_back(con);
			continue;
		}

		if (con.type == ContainerType::BinaryOp)
		{
			Container c2 = result_stack.back();
			result_stack.pop_back();

			Container c1 = result_stack.back();
			result_stack.pop_back();

			eval_expr(con, c1, c2);
		}
	}
}


int Evaluator::yield()
{
	int num = result_stack.back().value.i;
	result_stack.pop_back();
	return num;
}
