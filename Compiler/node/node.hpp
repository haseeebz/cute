#include <cstdint>
#include <string>
#include <vector>

#pragma once


enum class NodeType
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


namespace Node
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
		NodeType nt;
	};

	struct Object     : Base{};
	struct Statement  : Base{};
	struct Expression : Base{};


	struct RootProgram : Object
	{
		Source* src;
		RootProgram() {{nt = NodeType::RootProgram;}};
		~RootProgram();
	};

	struct Source : Object
	{
		std::vector<Function*> functions;

		Source() {{nt = NodeType::Source;}};
		~Source();
	};


	struct Function : Object
	{
		Identifier* name;
		std::vector<Declaration*> parameters;
		std::vector<Statement*>   statements;

		Function() {{nt = NodeType::Function;}};
		~Function();
	};

	
	// Statement Nodes
	struct Declaration : Statement
	{	

		Identifier* type;
		Identifier* name;

		Declaration() {nt = NodeType::Declaration;};
		~Declaration();
	};

	struct Assignment : Statement
	{

		Identifier* name;
		Expression* value;

		Assignment() {nt = NodeType::Assignment;};
		~Assignment();
	};

	struct ExprStatment : Statement
	{

		Expression* expr;

		ExprStatment(Expression* expr): expr(expr) {{nt = NodeType::ExprStatement;}};
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

		Int(std::string i): raw(i) {nt = NodeType::Int;};
	};


	struct Float : Expression
	{
		std::string raw;
		union
		{
			float  f32;
			double f64;
		} val;

		Float(std::string f): raw(f) {nt = NodeType::Float;};
	};


	struct Identifier : Expression
	{
		std::string val;

		Identifier(std::string val): val(val) {{nt = NodeType::Identifier;}};
	};


	struct BinaryOp : Expression
	{
		enum class Type
		{
			Add,
			Sub,
			Mul,
			Div
		};

		Type op;
		Expression* left;
		Expression* right;

		BinaryOp() {nt = NodeType::BinaryOp;};
		BinaryOp(Type op, Expression* left, Expression* right): op(op), left(left), right(right) {nt = NodeType::BinaryOp;};
		~BinaryOp();
	};


	struct FunctionCall : Expression
	{
		Identifier* name;
		std::vector<Expression*> args;

		FunctionCall() {nt = NodeType::FunctionCall;};
		FunctionCall(Identifier* name): name(name) {{nt = NodeType::FunctionCall;}};
		~FunctionCall();
	};

};



