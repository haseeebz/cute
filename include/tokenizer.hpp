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

	public:

	ContainerVec* tokenize(std::string str);
};


