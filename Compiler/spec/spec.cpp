#include <cstddef>
#include <cstdint>
#include <exception>
#include <map>
#include <string>

#include "spec.hpp"


bool CtSpec::strToI32(std::string& str, int32_t& i)
{
	try 
	{
		size_t pos;
		i = std::stoi(str, &pos);
		if (pos != str.size()) {return false;}
	} 
	catch (std::exception) 
	{
		return false;
	}

	return true;
}


bool CtSpec::strToI64(std::string& str, int64_t& i)
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


bool CtSpec::strToU32(std::string& str, uint32_t& i)
{
	try
	{
		size_t pos;
		uint64_t v = std::stoul(str, &pos);
		if (pos != str.size()) {return false;}

		if (v > UINT32_MAX) { return false; }

		i = static_cast<uint32_t>(v);
	} 
	catch (std::exception) 
	{
		return false;
	}

	return true;
}


bool CtSpec::strToU64(std::string& str, uint64_t& i)
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


bool CtSpec::strToF32(std::string& str, float& i)
{
	try 
	{
		size_t pos;
		i = std::stof(str, &pos);
		if (pos != str.size()) {return false;}
	} 
	catch (std::exception) 
	{
		return false;
	}

	return true;
}


bool CtSpec::strToF64(std::string& str, double& i)
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
