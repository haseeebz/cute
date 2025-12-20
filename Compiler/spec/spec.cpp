#include <cstddef>
#include <cstdint>
#include <exception>
#include <map>
#include <string>

#include "spec.hpp"


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
