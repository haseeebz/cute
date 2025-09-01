#include <iostream>
#include <string>
#include <vector>
#include "container.hpp"

#pragma once

class Tokenizer
{
	int index;
	std::string current_string;
	ContainerVec* tokenized_containers;
	Container prev_container = Container();

	char nextChar();
	void backtrack();

	char tokenizeSpace();
	void tokenizeDigit(char c);
	void tokenizeOp(char c);
	void tokenizePoint();

	public:

	ContainerVec* tokenize(std::string str);
};


