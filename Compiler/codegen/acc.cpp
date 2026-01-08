#include "units.hpp"


void Codegen::Accumulator::writeback(const std::string& str)
{
	this->code.append(str);
}

void Codegen::Accumulator::writeback(const std::string&& str)
{
	this->code.append(str);
}

const std::string& Codegen::Accumulator::accumulate(RootUnit& unit)
{
	unit.accept(this);
	return this->code;
}
