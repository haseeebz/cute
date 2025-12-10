#include "CuteSpec.hpp"
#include <string>
#include <sys/types.h>
#include <vector>

#pragma once 


enum CtTokenType 
{
	Int,
	Float,
	Word,
	Symbol,
	Keyword,
	EndOfLine,
	EndOfFile,
	Invalid
};


struct CtToken
{
	CtTokenType type;
	
	union
	{
		struct
		{
			uint start;
			uint end;
		} view;
		CtSpec::KeyWord keyword;
		CtSpec::Symbol  sym;
	} val;
	
	CtToken() = default;
	CtToken(CtTokenType t) : type(t) {}
	CtToken(CtTokenType t, uint s, uint e) : type(t) {val.view.start = s; val.view.end = e;};
	CtToken(CtSpec::KeyWord keyword) : type(CtTokenType::Keyword) {val.keyword = keyword;}
	CtToken(CtSpec::Symbol sym) : type(CtTokenType::Symbol) {val.sym = sym;}
};


class CtTokenStream
{
	std::vector<CtToken> tokens;
	uint curr_token;
	std::string srcStr;

	public:


	CtTokenStream() {};
	CtTokenStream(std::string src);

	void add(CtToken token);
	std::string toString();
	

	CtToken next(); 
	CtToken peek(); 
	uint currentIndex();
	void backtrack(uint i = 1);
	void gotoIndex(uint i);	

	std::string viewToken(CtToken *token);
	

	// get___ functions write the indicated token's content to the passed pointer and return true
	// if token is not of expected type, it returns false and does'nt move forward

	bool getWord(std::string *str);

	bool getInt(std::string *d);
	bool getFloat(std::string *f);

	bool getKeyword(CtSpec::KeyWord *key);
	bool getSymbol(CtSpec::Symbol *sym);

	// obtain___ functions expect a particular keyword/sym and return true

	bool obtainKeyword(CtSpec::KeyWord key);
	bool obtainSymbol(CtSpec::Symbol sym);

	// returns true if the next token is of the indicated type and updates the token
	bool expectType(CtTokenType t, CtToken *token);
};


class CtTokenizer 
{
	CtTokenStream currStream;

	std::string *currSrc;
	uint currIndex;

	void tokenizeNumber();
	void tokenizeSymbol();
	void tokenizeWord();

	public:

	CtTokenStream tokenize(std::string input_file);
};