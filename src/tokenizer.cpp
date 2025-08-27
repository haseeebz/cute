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

		Container con;
		
		switch (c) 
		{

		case '+' : con = Container(BinaryOpType::Add); break;
		case '-' : con = Container(BinaryOpType::Sub); break;
		case '*' : con = Container(BinaryOpType::Mul); break;
		case '/' : con = Container(BinaryOpType::Div); break;
			
		case '(' : con = Container(ParanType::Left); break;
		case ')' : con = Container(ParanType::Right); break;

		default: continue;
		}

		if (con.type == ContainerType::Void) {continue;} //Error raising here.

		tokenized_containers->push_back(con);
		prev_container = con;
	}

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
			std::cout << "[ Int " << current.value.i << " ] ";
			continue;
		}

		if (current.type == ContainerType::BinaryOp)
		{
			std::cout << "[ BinaryOp " << binaryOp_to_char(current.value.op) << " ] ";
			continue;
		}

		if (current.type == ContainerType::Paran)
		{
			char paran = (current.value.paran == ParanType::Left) ? '(' : ')';
			std::cout << "[ Paran " << paran << " ] ";
			continue;
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