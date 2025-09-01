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
	current_string = str;
	index = 0;
	char c;

	while (index < str.length())
	{
		c = nextChar();
		
		if (std::isspace(c)) {continue;}

		if (std::isdigit(c))
		{
			tokenizeDigit(c);
			continue;
		}

		tokenizeOp(c);
	}

	return tokenized_containers;
}


char Tokenizer::nextChar()
{
	char c = current_string[index];
	index++;
	return c;
}



void Tokenizer::tokenizeDigit(char c)
{
	int num = std::atoi(&c);

	while (true)
	{
		c = nextChar();
		
		if (std::isdigit(c))
		{
			num = num * 10 + std::atoi(&c);
			continue;
		}

		break;
	}

	Container con(num);
	tokenized_containers->push_back(con);
	prev_container = con;

}


void Tokenizer::tokenizeOp(char c)
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

	default  : con = Container(ContainerType::Void);
	}

	if (con.type == ContainerType::Void) {return;} //Error raising here.

	tokenized_containers->push_back(con);
	prev_container = con;
}


