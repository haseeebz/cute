#include "token.hpp"

#include "tokenizer.hpp"

#include <cctype>
#include <string>


void Tokenizer::tokenize(std::string str)
{
	currStr = str;

	for (strIndex = 0; strIndex < currStr.length(); strIndex++)
	{
		if (currStr[strIndex] == ' ') {continue;}

		if (std::isdigit(currStr[strIndex]))
		{
			tokenizeNumber();
			continue;
		}

		tokenizeSymbol();
	}
}


void Tokenizer::tokenizeNumber()
{
	std::string str;
	bool isFloat = false;

	while (true) 
	{
		if (std::isdigit(currStr[strIndex]))
		{
			str.push_back(currStr[strIndex]);
			strIndex++;
			continue;
		}

		if (currStr[strIndex] == '.')
		{
			str.push_back('.');
			isFloat = true;
			strIndex++;
			continue;
		}

		break;
	}

	TokenType type = isFloat ? TokenType::tokenFloat : TokenType::tokenInt;
	Token token(type, str);
	tokens.push_back(token);
}


void Tokenizer::tokenizeSymbol()
{

}