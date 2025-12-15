#include "../spec/syntax.hpp"

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
	struct ExprStatment;
	
	// Expression Nodes
	struct Int;
	struct Float;
	struct Identifier;
	struct BinaryOp;
	struct FunctionCall;
	struct Assignment;


	// Defintions


	struct Base
	{
		CtNodeType nt;
	};

	struct Object     : Base{};
	struct Statement  : Base{};
	struct Expression : Base{std::string result_type;};


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
		CtSyntax::Symbol op;
		Expression* left;
		Expression* right;
		BinaryOp() {nt = CtNodeType::BinaryOp;};
		BinaryOp(CtSyntax::Symbol op, Expression* left, Expression* right): op(op), left(left), right(right) {nt = CtNodeType::BinaryOp;};
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

	struct Assignment : Expression
	{
		Identifier* name;
		Expression* value;

		Assignment() {nt = CtNodeType::Assignment;};
		~Assignment();
	};

};




class CtNodeWalker
{
	virtual void handleRoot(CtNode::RootProgram *node) = 0;
	virtual void handleSource(CtNode::Source *node) = 0;

	virtual void handleFunction(CtNode::Function *node) = 0;

	virtual void handleDeclaration(CtNode::Declaration *node) = 0;
	virtual void handleAssignment(CtNode::Assignment *node) = 0;

	virtual void handleInt(CtNode::Int *node) = 0;
	virtual void handleFloat(CtNode::Float *node) = 0;
	virtual void handleBinaryOp(CtNode::BinaryOp *node) = 0;
	virtual void handleIdentifier(CtNode::Identifier *node) = 0;
	virtual void handleFunctionCall(CtNode::FunctionCall *node) = 0;

	public:
	
	void walk(CtNode::Base* node);
};


class CtNodePrinter: public CtNodeWalker
{
	int indent = 0;

	void printIndent();

	void handleRoot(CtNode::RootProgram *node);
	void handleSource(CtNode::Source *node);

	void handleFunction(CtNode::Function *node);

	void handleDeclaration(CtNode::Declaration *node);
	void handleAssignment(CtNode::Assignment *node);

	void handleInt(CtNode::Int *node);
	void handleFloat(CtNode::Float *node);
	void handleBinaryOp(CtNode::BinaryOp *node);
	void handleIdentifier(CtNode::Identifier *node);
	void handleFunctionCall(CtNode::FunctionCall *node);
	
	public:

	void print(CtNode::Base *node);
};