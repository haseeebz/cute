#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include "../include/container.hpp"




void print_container(Container& container, bool endline)
{
	if (container.type == ContainerType::Int)
	{
		std::cout << "[ Int " << container.value.i << " ] ";
	}

	if (container.type == ContainerType::BinaryOp)
	{
		std::cout << "[ BinaryOp " << binaryOp_to_char(container.value.op) << " ] ";
	}

	if (container.type == ContainerType::Paran)
	{
		char paran = (container.value.paran == ParanType::Left) ? '(' : ')';
		std::cout << "[ Paran " << paran << " ] ";
	}

	if (endline) {std::cout << std::endl;}

}


void print_containers(ContainerVec* containers)
{
	Container current;
	for (int i = 0; i < containers->size(); i++)
	{
		current = containers->at(i);
		print_container(current, false);
	}
	std::cout << std::endl;

}


char binaryOp_to_char(BinaryOpType op)
{
	switch (op) 
	{
		case BinaryOpType::Add : return '+'; break;
		case BinaryOpType::Sub : return '-'; break;
		case BinaryOpType::Mul : return '*'; break;
		case BinaryOpType::Div : return '/'; break;
		case BinaryOpType::Pow : return '^'; break;
		default: return '?';
	}
}