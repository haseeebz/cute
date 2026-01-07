#include "../node/node.hpp"

#include "../tokenizer/token.hpp"


#pragma once

using Sym = CtLang::Symbol;
using Bin = CtLang::BinaryOpType;
using Un  = CtLang::UnaryOpType;

inline const std::map<Sym, Bin> symToBinaryOp 
{
    { Sym::Plus,          Bin::Add },
    { Sym::Minus,         Bin::Sub },
    { Sym::Star,          Bin::Mul },
    { Sym::Slash,         Bin::Div },
    { Sym::Percentage,    Bin::Mod },

    { Sym::DoubleEqual,   Bin::Equal },
    { Sym::NotEqual,      Bin::NotEqual },
    { Sym::Greater,       Bin::Greater },
    { Sym::GreaterEqual,  Bin::GreaterEqual },
    { Sym::Lesser,        Bin::Lesser },
    { Sym::LesserEqual,   Bin::LesserEqual },

    { Sym::DoubleGreater, Bin::BitShiftRight },
    { Sym::DoubleLesser,  Bin::BitShiftLeft },

    { Sym::SingleBar,     Bin::BitOr },
    { Sym::SingleAnd,     Bin::BitAnd },
    { Sym::Exponent,      Bin::BitXor },

	{ Sym::DoubleBar,     Bin::LogicOr },
    { Sym::DoubleAnd,     Bin::LogicAnd },
};

inline const std::map<Sym, Un> symToUnaryOp 
{
    { Sym::Exclamation, Un::LogicNot },
    { Sym::Tilde,       Un::BitNot },  
    { Sym::Minus,       Un::Negation }
};


class CtParser
{
	std::string filepath;
	CtNode::Source *source;

	CtTokenizer tokenizer;
	CtTokenStream *tokens;

	void startParsingFile();

	CtNode::Function* parseFunction();

	CtNode::StmtBlock* parseBlock();

	CtNode::Statement* parseStatement();

	CtNode::Declaration* parseDeclaration();
	CtNode::Loop* parseLoop();
	CtNode::While* parseWhile();
	CtNode::For* parseFor();
	CtNode::If* parseIf();

	CtNode::Expression* parseExpression(uint prev_precedence = 0, uint depth = 0);
	CtNode::Expression* getLeafExpression(CtToken& token);


	public:

	CtNode::Source* parseFile(std::string filepath);

	CtNode::RootProgram* parse(std::string filepath);
};


