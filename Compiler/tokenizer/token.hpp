#include <string>
#include <sys/types.h>
#include <vector>

#pragma once 


enum CtTokenType 
{
	Int,
	Float,
	Symbol,
	Word,
	EndOfFile
};


struct CtToken
{
	CtTokenType type;
	uint start;
	uint end;

	CtToken() = default;
	CtToken(CtTokenType t, uint s, uint e) : type(t), start(s), end(e) {};
};


class CtTokenStream
{
	
	std::vector<CtToken> tokens;
	uint curr_token;

	public:

	std::string srcStr;

	CtTokenStream() {};
	CtTokenStream(std::string src);

	void add(CtToken token);
	std::string toString();
	

	CtToken next(); // gives you the current CtToken and increments the counter
	CtToken peek(); // gives you the current CtToken but does'nt increment
	uint currentIndex(); // gives you the current index duh
	void backtrack(uint i = 1); // backtracks the index by the given amount. 
	void gotoIndex(uint i);	// goes to the given index... duh...


	// viewing token
	std::string viewToken(CtToken *token);
	char viewSymToken(CtToken *token);

	// all of these functions try to get the specified type. 
	// if type found, it is written to the pointer, true is returned and the counter is increased
	// if not, it returns false, the pointer and the counter is'nt modified 
	bool getInt(std::string *str); 
	bool getFloat(std::string *str);
	bool getWord(std::string *str);
	bool getSym(char *sym);

	// returns true if the current CtToken is word AND matches the given string
	bool getKeyword(std::string keyword);
	bool getKeySym(char sym);

	bool expectType(CtTokenType type);
	
};


class CtTokenizer 
{
	CtTokenStream currStream;

	std::string *currSrc;
	uint currIndex;

	public:

	CtTokenStream tokenize(std::string input_file);
	void tokenizeNumber();
	void tokenizeSymbol();
	void tokenizeWord();
};