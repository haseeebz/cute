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

	uint line;

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
	CtToken(CtTokenType t, uint s, uint e) : type(t), line(0) {view.start = s; view.end = e;};
	CtToken(CtTokenType t, uint s, uint e, uint line) : type(t), line(line) {view.start = s; view.end = e;};
};


class CtTokenStream
{
	std::vector<CtToken> tokens;
	uint curr_token;
	std::string srcStr;

	

	public:


	CtTokenStream() {};
	CtTokenStream(std::string src);

	void raiseError(CtToken* token, std::string msg);
	
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
	
	bool getType(CtTokenType t, CtToken *token);
	bool getTypes(std::vector<CtTokenType> t, CtToken *token);
	bool getWord(std::string *str);
	bool getInt(std::string *d);
	bool getFloat(std::string *f);
	bool getKeyword(CtLang::KeyWord *key);
	bool getSymbol(CtLang::Symbol *sym);
	bool getKeywordSpecific(CtLang::KeyWord key);
	bool getSymbolSpecific(CtLang::Symbol sym);


	// expect_ functions behave the same as get but raise error too.

	void expectType(CtTokenType t, CtToken *token);
	void expectTypes(std::vector<CtTokenType> t, CtToken *token);
	void expectWord(std::string *str);
	void expectInt(std::string *d);
	void expectFloat(std::string *f);
	void expectKeyword(CtLang::KeyWord *key);
	void expectSymbol(CtLang::Symbol *sym);
	void expectKeywordSpecific(CtLang::KeyWord key);
	void expectSymbolSpecific(CtLang::Symbol sym);


	void consumeEOL();

};


class CtTokenizer 
{
	CtTokenStream currStream;

	const std::string *currSrc;
	uint currIndex;
	uint currLine;

	void tokenizeNumber();
	void tokenizeSymbol();
	void tokenizeWord();

	public:

	CtTokenStream tokenize(std::string input_file);
};