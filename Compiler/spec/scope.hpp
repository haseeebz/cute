#include <map>
#include <string>

#include "types.hpp"

#pragma once


struct CtScope 
{
	std::map<std::string, CtTypes::Info*> symbols;
};