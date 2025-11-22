#include <string>
#include <sys/types.h>
#include <vector>
#pragma once 


enum TokenType 
{
	tokenInt,
	tokenFloat,
	tokenSymbol,
	tokenWord,
	tokenEOF
};


struct Token
{
	TokenType type;
	uint start;
	uint end;

	Token() = default;
	Token(TokenType t, uint s, uint e) : type(t), start(s), end(e) {};
};


struct TokenStream
{
	std::string srcStr;

	std::vector<Token> tokens;
	uint curr_token;

	TokenStream() {};
	TokenStream(std::string src);
	void add(Token token);
	Token next();
	Token peek();
	void backtrack();
	std::string viewToken(Token* token);
	char viewSymToken(Token* token);
	std::string toString();
};


class Tokenizer 
{
	TokenStream currStream;

	std::string* currSrc;
	uint currIndex;

	public:

	TokenStream tokenize(std::string input_file);
	void tokenizeNumber();
	void tokenizeSymbol();
	void tokenizeWord();
};