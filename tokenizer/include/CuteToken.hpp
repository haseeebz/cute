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


class TokenStream
{
	
	std::vector<Token> tokens;
	uint curr_token;

	public:

	std::string srcStr;

	TokenStream() {};
	TokenStream(std::string src);

	void add(Token token);
	std::string toString();
	

	Token next(); // gives you the current token and increments the counter
	Token peek(); // gives you the current token but does'nt increment
	uint currentIndex(); // gives you the current index duh
	void backtrack(uint i = 1); // backtracks the index by the given amount. 
	void gotoIndex(uint i);	// goes to the given index... duh...


	// viewing token
	std::string viewToken(Token* token);
	char viewSymToken(Token* token);

	// all of these functions try to get the specified type. 
	// if type found, it is written to the pointer, true is returned and the counter is increased
	// if not, it returns false, the pointer and the counter is'nt modified 
	bool getInt(std::string* str); 
	bool getFloat(std::string* str);
	bool getWord(std::string* str);
	bool getSym(char* sym);

	// returns true if the current token is word AND matches the given string
	bool getKeyword(std::string keyword);
	bool getKeySym(char sym);

	bool expectType(TokenType type);
	
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