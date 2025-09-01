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

void Tokenizer::backtrack()
{
	index--;
}


void Tokenizer::tokenizeDigit(char c)
{
	int integar = std::atoi(&c);
	double decimal;
	double decimal_multiplier = 10;
	bool is_decimal = false;

	while (true)
	{
		c = nextChar();
		
		if (std::isdigit(c))
		{
			if (is_decimal)
			{
				decimal = decimal + (std::atoi(&c) / decimal_multiplier);
				decimal_multiplier = decimal_multiplier * 10;
				continue;
			}

			integar = integar * 10 + std::atoi(&c);
			continue;
		}

		if (c == '.')
		{
			decimal = (double) integar;
			is_decimal = true;
			continue;
		}

		backtrack();
		break;
	}

	Container con = is_decimal ? Container(decimal) : Container(integar);
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
		
	case '(' : con = Container(ParanType::Left); break;
	case ')' : con = Container(ParanType::Right); break;

	default  : con = Container(ContainerType::Void);
	}

	if (con.type == ContainerType::Void) {return;} //Error raising here.

	tokenized_containers->push_back(con);
	prev_container = con;
}


