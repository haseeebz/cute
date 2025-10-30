#include <string>
#include "token.hpp"


Token::Token(TokenType t, std::string s)
{
	type = t;
	str = s;	
}