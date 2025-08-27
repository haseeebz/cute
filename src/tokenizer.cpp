#include <cctype>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../include/container.hpp"
#include "../include/tokenizer.hpp"


ContainerVec* Tokenizer::tokenize(std::string str)
{
	tokenized_containers = new ContainerVec;

	char c;

	for (int i = 0; i < str.length(); i++)
	{
		c = str[i];
		
		if (std::isspace(c)) {continue;}

		if (std::isdigit(c))
		{
			int num = std::atoi(&c);

			if (prev_container.type == ContainerType::Int)
			{
				Container con = Container(prev_container.value.i * 10 + num);
				tokenized_containers->pop_back();
				tokenized_containers->push_back(con);
				prev_container = con;
				continue;
			}

			Container con = Container(num);
			tokenized_containers->push_back(con);
			prev_container = con;
			continue;
		}

		BinaryOpType op;
		switch (c) 
		{
		case '+' : op = BinaryOpType::Add; break;
		case '-' : op = BinaryOpType::Sub; break;
		case '*' : op = BinaryOpType::Mul; break;
		case '/' : op = BinaryOpType::Div; break;
		default: continue;
		}

		Container con = Container(op);
		tokenized_containers->push_back(con);
		prev_container = con;
	}
	print_containers(tokenized_containers);
	return tokenized_containers;
}


void print_containers(ContainerVec* containers)
{
	Container current;
	for (int i = 0; i < containers->size(); i++)
	{
		current = containers->at(i);

		if (current.type == ContainerType::Int)
		{
			std::cout << "[Int " << current.value.i << "] ";
			continue;
		}

		if (current.type == ContainerType::BinaryOp)
		{
			std::cout << "[BinaryOp " << binaryOp_to_char(current.value.op) << "] ";
		}

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
		default: return '?';
	}
}