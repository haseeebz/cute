#include <vector>
#include <iostream>


enum TokenType 
{
	Int,
	Op,
	Void
};


struct Token 
{
	TokenType type;
	union {
		int i;
		char op;
	} value;
};


class Tokenizer
{
	std::string current_string;
	
	public:
	
	std::vector<Token>* tokenize(std::string str);
	void print_tokens(std::vector<Token>* tokens);
}