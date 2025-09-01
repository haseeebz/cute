#include <iostream>
#include <string>
#include <vector>
#include "container.hpp"

#pragma once

class Tokenizer
{
	std::string current_string;
	ContainerVec* tokenized_containers;
	Container prev_container = Container();

	void tokenize_digit(char c);
	void tokenize_op(char c);

	public:

	ContainerVec* tokenize(std::string str);
};


