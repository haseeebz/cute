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
			tokenize_digit(c);
			continue;
		}

		tokenize_op(c);
	}

	return tokenized_containers;
}


void Tokenizer::tokenize_digit(char c)
{
	int num = std::atoi(&c);

	if (prev_container.type == ContainerType::Int)
	{
		Container con = Container(prev_container.value.i * 10 + num);
		tokenized_containers->pop_back();
		tokenized_containers->push_back(con);
		prev_container = con;
		return;
	}

	Container con = Container(num);
	tokenized_containers->push_back(con);
	prev_container = con;
}


void Tokenizer::tokenize_op(char c)
{
		Container con;
		
		switch (c) 
		{

		case '+' : con = Container(BinaryOpType::Add); break;
		case '-' : con = Container(BinaryOpType::Sub); break;
		case '*' : con = Container(BinaryOpType::Mul); break;
		case '/' : con = Container(BinaryOpType::Div); break;
		case '^' : con = Container(BinaryOpType::Pow); break;
			
		case '(' : con = Container(ParanType::Left); break;
		case ')' : con = Container(ParanType::Right); break;

		default: return;
		}

		if (con.type == ContainerType::Void) {return;} //Error raising here.

		tokenized_containers->push_back(con);
		prev_container = con;
}
