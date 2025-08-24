#include <cctype>
#include <iostream>
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
		case '-' : op = BinaryOpType::Add; break;
		case '*' : op = BinaryOpType::Add; break;
		case '/' : op = BinaryOpType::Add; break;
		default: continue;
		}

		Container con = Container(op);
		tokenized_containers->push_back(con);
	}

	return tokenized_containers;
}


