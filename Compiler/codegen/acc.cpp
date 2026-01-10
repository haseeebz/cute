#include "units.hpp"
#include <iostream>


void Codegen::Accumulator::writeback(const std::string& str)
{
	this->code.append(str);
	std::cout << code << "\n";
}

void Codegen::Accumulator::writeback(const std::string&& str)
{
	this->code.append(str);
	std::cout << code << "\n";
}

const std::string& Codegen::Accumulator::accumulate(Unit* unit)
{
	unit->accept(this);
	return this->code;
}
