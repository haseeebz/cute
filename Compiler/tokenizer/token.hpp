#include <string>
#include <sys/types.h>
#include <vector>

#include "../spec/lang.hpp"

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
		CtLang::KeyWord keyword;
		CtLang::Symbol  sym;
	} val;
	
	struct
	{
		uint start;
		uint end;
	} view;

	CtToken() = default;
	CtToken(CtTokenType t) : type(t) {}
	CtToken(CtTokenType t, uint s, uint e) : type(t) {view.start = s; view.end = e;};
};


class CtTokenStream
{
	std::vector<CtToken> tokens;
	uint curr_token;
	std::string srcStr;

	public:


	CtTokenStream() {};
	CtTokenStream(std::string src);

	// Gives the source string the stream points to.
	const std::string* source();

	// Add a token to the stream. Should only used by the tokenizer.
	void add(CtToken token);

	// Converts all the tokens to a nice string
	std::string toString();
	
	// Get the next token and increment
	CtToken next(); 

	// Get the next token and don't increment
	CtToken peek(); 

	// Get the current index... duh
	uint currentIndex();

	// Backtrack the tokens by a given amount
	void backtrack(uint i = 1);

	// Goto a specific index. i = 0 to reset the token stream and go to the beginning
	void gotoIndex(uint i);	

	// View the contents of a token
	std::string viewToken(CtToken *token);
	

	// get_ functions return true , write the value to the pointer and increment if the next token is of the specified type.
	bool getWord(std::string *str);
	// get_ functions return true , write the value to the pointer and increment if the next token is of the specified type.
	bool getInt(std::string *d);
	// get_ functions return true , write the value to the pointer and increment if the next token is of the specified type.
	bool getFloat(std::string *f);
	// get_ functions return true , write the value to the pointer and increment if the next token is of the specified type.
	bool getKeyword(CtLang::KeyWord *key);
	// get_ functions return true , write the value to the pointer and increment if the next token is of the specified type.
	bool getSymbol(CtLang::Symbol *sym);

	// expect___ functions expect a particular keyword/sym, return true and increment the counter
	bool expectKeyword(CtLang::KeyWord key);
	// expect___ functions expect a particular keyword/sym, return true and increment the counter
	bool expectSymbol(CtLang::Symbol sym);

	// expect a specific token type, write the token and return true if the type matches. *token can be NULL if you don't want the value.
	bool expectType(CtTokenType t, CtToken *token);
};


class CtTokenizer 
{
	CtTokenStream currStream;

	const std::string *currSrc;
	uint currIndex;

	void tokenizeNumber();
	void tokenizeSymbol();
	void tokenizeWord();

	public:

	CtTokenStream tokenize(std::string input_file);
};