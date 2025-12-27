#include <cstddef>
#include <cstdint>
#include <exception>
#include <map>
#include <string>

#include "spec.hpp"


using Bin = CtSpec::BinaryOpType;

bool CtSpec::isArithmetic(Bin op)
{
	switch (op) 
	{
		case Bin::Add:
		case Bin::Sub:
		case Bin::Mul:
		case Bin::Div:
		case Bin::Mod:
		return true;
		default: 
		return false;
	}
}

bool CtSpec::isComparison(CtSpec::BinaryOpType op)
{
	switch (op) 
	{
		case Bin::Greater:
		case Bin::GreaterEqual:
		case Bin::Lesser:
		case Bin::LesserEqual:
		case Bin::Equal:
		case Bin::NotEqual:
		return true;
		default: 
		return false;
	}
}

bool CtSpec::isLogical(CtSpec::BinaryOpType op)
{
	switch (op) 
	{
		case Bin::LogicAnd:
		case Bin::LogicOr:
		return true;
		default: 
		return false;
	}
}

bool CtSpec::isBitwise(CtSpec::BinaryOpType op)
{
	switch (op) 
	{
		case Bin::BitAnd:
		case Bin::BitOr:
		case Bin::BitXor:
		case Bin::BitShiftRight:
		case Bin::BitShiftLeft:
		return true;
		default: 
		return false;
	}
}


bool CtSpec::strToInt(std::string& str, int64_t& i)
{
	try 
	{
		size_t pos;
		i = std::stoll(str, &pos);
		if (pos != str.size()) {return false;}
	} 
	catch (std::exception) 
	{
		return false;
	}

	return true;
}


bool CtSpec::strToUInt(std::string& str, uint64_t& i)
{
	try 
	{
		size_t pos;
		uint64_t v = std::stoull(str, &pos);

		if (pos != str.size()) {return false;}

		i = static_cast<uint64_t>(v);

	} 
	catch (std::exception) 
	{
		return false;
	}

	return true;
}


bool CtSpec::strToFloat(std::string& str, double& i)
{
	try 
	{
		size_t pos;
		i = std::stod(str, &pos);
		if (pos != str.size()) {return false;}
	} 
	catch (std::exception) 
	{
		return false;
	}

	return true;
}
