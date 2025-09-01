#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>
#include "../include/container.hpp"
#include "../include/eval.hpp"


void Evaluator::evalExpr(Container& op, Container& c1, Container& c2)
{
	Container result;

	switch (op.value.op) 
	{
		case BinaryOpType::Add : result = add(c1, c2); break;
		case BinaryOpType::Sub : result = subtract(c1, c2); break;
		case BinaryOpType::Mul : result = multiply(c1, c2); break;
		case BinaryOpType::Div : result = divide(c1, c2); break;
		default: return;
	}

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

			evalExpr(con, c1, c2);
		}
	}
}


int Evaluator::yield()
{
	int num = result_stack.back().value.i;
	result_stack.pop_back();
	return num;
}


Container Evaluator::add(Container& c1, Container& c2)
{
	if (c1.type == ContainerType::Int && c2.type == ContainerType::Int)
	{
		return Container(c1.value.i + c2.value.i);
	} else 
	{
		double a = (c1.type == ContainerType::Double) ? c1.value.d : (double) c1.value.i;
		double b = (c2.type == ContainerType::Double) ? c2.value.d : (double) c2.value.i;
		return Container(a + b);
	}
}


Container Evaluator::subtract(Container& c1, Container& c2)
{
		if (c1.type == ContainerType::Int && c2.type == ContainerType::Int)
	{
		return Container(c1.value.i - c2.value.i);
	} else 
	{
		double a = (c1.type == ContainerType::Double) ? c1.value.d : (double) c1.value.i;
		double b = (c2.type == ContainerType::Double) ? c2.value.d : (double) c2.value.i;
		return Container(a - b);
	}
}


Container Evaluator::multiply(Container& c1, Container& c2)
{
	if (c1.type == ContainerType::Int && c2.type == ContainerType::Int)
	{
		return Container(c1.value.i * c2.value.i);
	} else 
	{
		double a = (c1.type == ContainerType::Double) ? c1.value.d : (double) c1.value.i;
		double b = (c2.type == ContainerType::Double) ? c2.value.d : (double) c2.value.i;
		return Container(a * b);
	}
}


Container Evaluator::divide(Container& c1, Container& c2)
{
	double a = (c1.type == ContainerType::Double) ? c1.value.d : (double) c1.value.i;
	double b = (c2.type == ContainerType::Double) ? c2.value.d : (double) c2.value.i;
	return Container(a / b);
}

