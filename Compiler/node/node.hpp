#include "CuteSpec.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#pragma once


enum class CtNodeType
{
	RootProgram,
	Source,
	Function,

	Declaration,
	Assignment,
	ExprStatement,

	Int,
	Float,
	Identifier,
	BinaryOp,
	FunctionCall
};


namespace CtNode
{
	struct Base;

	struct Object;
	struct Statement;
	struct Expression;

	// Object Nodes
	struct RootProgram;
	struct Source;
	struct Function;

	
	// Statement Nodes
	struct Declaration;
	struct Assignment;
	struct ExprStatment;
	
	// Expression Nodes
	struct Int;
	struct Float;
	struct Identifier;
	struct BinaryOp;
	struct FunctionCall;


	// Defintions


	struct Base
	{
		CtNodeType nt;
	};

	struct Object     : Base{};
	struct Statement  : Base{};
	struct Expression : Base{};


	struct RootProgram : Object
	{
		Source* src;
		RootProgram() {{nt = CtNodeType::RootProgram;}};
		~RootProgram();
	};

	struct Source : Object
	{
		std::map<std::string, Function*> functions;

		Source() {{nt = CtNodeType::Source;}};
		~Source();
	};


	struct Function : Object
	{
		Identifier* name;
		std::vector<Declaration*> parameters;
		std::vector<Statement*>   statements;

		Function() {{nt = CtNodeType::Function;}};
		~Function();
	};

	
	// Statement Nodes
	struct Declaration : Statement
	{	

		Identifier* type;
		Identifier* name;

		Declaration() {nt = CtNodeType::Declaration;};
		~Declaration();
	};

	struct Assignment : Statement
	{

		Identifier* name;
		Expression* value;

		Assignment() {nt = CtNodeType::Assignment;};
		~Assignment();
	};

	struct ExprStatment : Statement
	{
		Expression* expr;

		ExprStatment(Expression* expr): expr(expr) {{nt = CtNodeType::ExprStatement;}};
		~ExprStatment();
	};
	
	
	// Expression Nodes
	struct Int : Expression
	{
		std::string raw;
		union
		{
			int32_t  i32;
			int64_t  i64;
			uint32_t u32;
			uint64_t u64;
		} val;

		Int(std::string i): raw(i) {nt = CtNodeType::Int;};
	};


	struct Float : Expression
	{
		std::string raw;
		union
		{
			float  f32;
			double f64;
		} val;

		Float(std::string f): raw(f) {nt = CtNodeType::Float;};
	};


	struct Identifier : Expression
	{
		std::string val;

		Identifier(std::string val): val(val) {{nt = CtNodeType::Identifier;}};
	};


	struct BinaryOp : Expression
	{
		CtSpec::Symbol op;
		Expression* left;
		Expression* right;

		BinaryOp() {nt = CtNodeType::BinaryOp;};
		BinaryOp(CtSpec::Symbol op, Expression* left, Expression* right): op(op), left(left), right(right) {nt = CtNodeType::BinaryOp;};
		~BinaryOp();
	};


	struct FunctionCall : Expression
	{
		Identifier* name;
		std::vector<Expression*> args;

		FunctionCall() {nt = CtNodeType::FunctionCall;};
		FunctionCall(Identifier* name): name(name) {{nt = CtNodeType::FunctionCall;}};
		~FunctionCall();
	};

};




class CtNodeWalker
{
	public:

	void walk(CtNode::Base* Ctnode);

	virtual void handleRoot(CtNode::RootProgram *Ctnode) = 0;
	virtual void handleSource(CtNode::Source *Ctnode) = 0;

	virtual void handleFunction(CtNode::Function *Ctnode) = 0;

	virtual void handleDeclaration(CtNode::Declaration *Ctnode) = 0;
	virtual void handleAssignment(CtNode::Assignment *Ctnode) = 0;

	virtual void handleInt(CtNode::Int *Ctnode) = 0;
	virtual void handleFloat(CtNode::Float *Ctnode) = 0;
	virtual void handleBinaryOp(CtNode::BinaryOp *Ctnode) = 0;
	virtual void handleIdentifier(CtNode::Identifier *Ctnode) = 0;
	virtual void handleFunctionCall(CtNode::FunctionCall *Ctnode) = 0;
};


class CtNodePrinter: public CtNodeWalker
{
	int indent = 0;
	void printIndent();
	
	public:

	void reset();

	void handleRoot(CtNode::RootProgram *Ctnode);
	void handleSource(CtNode::Source *Ctnode);

	void handleFunction(CtNode::Function *Ctnode);

	void handleDeclaration(CtNode::Declaration *Ctnode);
	void handleAssignment(CtNode::Assignment *Ctnode);

	void handleInt(CtNode::Int *Ctnode);
	void handleFloat(CtNode::Float *Ctnode);
	void handleBinaryOp(CtNode::BinaryOp *Ctnode);
	void handleIdentifier(CtNode::Identifier *Ctnode);
	void handleFunctionCall(CtNode::FunctionCall *Ctnode);
};