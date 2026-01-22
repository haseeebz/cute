#include <string>
#include <vector>

#pragma once


enum class CtGenNodeType
{
	Root,
	Source,
	Function,
	Struct,
	Directive,

	StmtBlock,
	Assignment,
	Declaration,
	ExprStmt,
	While,
	For,
	If,

	Literal,
	Identifier,
	BinaryOp,
	UnaryOp,
	Call
};

namespace CtGenNode
{
	struct Base;

	struct Object;
	struct Statement;
	struct Expression;
	
	struct Root;
	struct Source;
	struct Function;
	struct Struct;
	struct Directive;

	struct StmtBlock;
	struct Assignment;
	struct Declaration;
	struct ExprStmt;
	struct While;
	struct For;
	struct If;
	
	struct Literal;
	struct Identifier;
	struct BinaryOp;
	struct UnaryOp;
	struct Call;


	struct Base
	{
		CtGenNodeType nt;
	};

	struct Root : Base
	{
		Source* src;

		Root() {nt = CtGenNodeType::Root;}

		~Root();
	};

	struct Source : Base
	{
		std::vector<Object*> objects;

		Source() {nt = CtGenNodeType::Source;}

		~Source();
	};

	struct Object : Base {};
	struct Statement : Base {};
	struct Expression : Base {};

	struct Function : Object
	{
		std::string name;
		std::string return_type;
		std::vector<Declaration*> parameters;
		StmtBlock* body;

		Function() {nt = CtGenNodeType::Function;}

		~Function();
	};

	struct Struct : Object
	{
		std::string name;
		std::vector<Declaration*> fields;
		std::vector<Function*> methods;

		Struct() {nt = CtGenNodeType::Function;}
		~Struct();
	};

	struct Directive : Object
	{
		std::string name;
		std::string content;

		Directive() {nt = CtGenNodeType::Directive;}
	};

	struct StmtBlock : Statement
	{
		std::vector<Statement*> body;

		StmtBlock() {nt = CtGenNodeType::StmtBlock;}
		~StmtBlock();
	};

	struct Assignment : Statement
	{
		std::string var;
		Expression* val;

		Assignment() {nt = CtGenNodeType::Assignment;}
		~Assignment();
	};

	struct Declaration : Statement
	{
		std::string type;
		std::string var;
		Expression* val;

		Declaration() {nt = CtGenNodeType::Declaration;}
		~Declaration();
	};

	struct ExprStmt : Statement
	{
		Expression* expr;

		ExprStmt() {nt = CtGenNodeType::ExprStmt;}
		~ExprStmt();
	};

	struct While : Statement
	{
		Expression* condition;
		StmtBlock* body;

		While() {nt = CtGenNodeType::While;}
		~While();		
	};

	struct For : Statement
	{
		Statement* init;
		Expression* condition;
		Expression* step;
		StmtBlock* body;

		For() {nt = CtGenNodeType::For;}
		~For();	
	};

	struct If : Statement
	{
		Expression* condition;
		StmtBlock* then_block;
		Statement* else_block;

		If() {nt = CtGenNodeType::If;}
		~If();	
	};
	
	struct Literal : Expression
	{
		std::string val;

		Literal() {nt = CtGenNodeType::Literal;}
		~Literal();	
	};

	struct Identifier : Expression
	{
		std::string val;

		Identifier() {nt = CtGenNodeType::Identifier;}
		~Identifier();	
	};

	struct BinaryOp : Expression
	{
		Expression* lhs;
		Expression* rhs;
		std::string op;

		BinaryOp() {nt = CtGenNodeType::BinaryOp;}
		~BinaryOp();
	};

	struct UnaryOp : Expression
	{
		Expression* expr;
		std::string op;
		bool prefix = true;

		UnaryOp() {nt = CtGenNodeType::UnaryOp;}
		~UnaryOp();
	};

	struct Call : Expression
	{
		std::string caller;
		std::vector<Expression*> args;

		Call() {nt = CtGenNodeType::Call;}
		~Call();
	};

}