#include <cstddef>
#include <string>
#include <vector>

#pragma once

namespace Codegen
{
	struct Unit;

	struct RootUnit;

	struct StmtUnit;
	struct BlockUnit;

	struct ExprUnit;

	struct DeclUnit;
	struct AssignUnit;

	struct LiteralUnit;
	struct IdentifierUnit;
	struct BinaryOpUnit;
	struct UnaryOpUnit;

	struct CallUnit;

	struct FuncDeclUnit;
	struct FuncDefUnit;

	struct StructDeclUnit;
	struct StructDefUnit;

	struct DirectiveUnit;


	class Accumulator
	{
		std::string code;

		public:
		
		void writeback(const std::string& str);
		void writeback(const std::string&& str);

		const std::string& accumulate(RootUnit& unit);
	};


	struct Unit
	{
		virtual ~Unit() {}
		virtual void accept(Accumulator* acc) = 0;
	};


	struct RootUnit : Unit
	{
		std::vector<Unit*> units;

		RootUnit(std::vector<Unit*>&& units_) : units(units_) {}

		~RootUnit()
		{
			for (auto u : units)
			{
				delete u;
			}		
		}

		void accept(Accumulator* acc) override
		{
			for (auto& u : units)
			{
				u->accept(acc);
				acc->writeback("\n");
			}	
		}
	};


	struct BlockUnit : Unit
	{
		std::vector<Unit*> units;

		BlockUnit(std::vector<Unit*> units_)
		: units(units_) {}

		~BlockUnit()
		{
			for (auto u : units)
				delete u;
		}

		void accept(Accumulator* acc) override
		{
			acc->writeback("{");
			for (auto& u : units)
			{
				u->accept(acc);
				acc->writeback(";");
			}
			acc->writeback("}");
		}
	};

	struct ExprUnit : Unit
	{
		ExprUnit() = default;
	};


	struct DeclUnit : Unit
	{
		std::string type;
		std::string name;

		DeclUnit(std::string type_, std::string name_): type(std::move(type_)), name(std::move(name_)) {}

		void accept(Accumulator* acc) override
		{
			acc->writeback(type);
			acc->writeback(" ");
			acc->writeback(name);
		}
	};


	struct AssignUnit : Unit
	{
		ExprUnit* lhs;
		ExprUnit* val;

		AssignUnit(ExprUnit* lhs_, ExprUnit* val_): lhs(lhs_), val(val_){}

		~AssignUnit()
		{
			delete lhs;
			delete val;
		}

		void accept(Accumulator* acc) override
		{
			lhs->accept(acc);
			acc->writeback("=");
			val->accept(acc);
		}
	};


	struct LiteralUnit : ExprUnit
	{
		std::string val;

		LiteralUnit(std::string val_): val(std::move(val_)){}

		void accept(Accumulator* acc) override
		{
			acc->writeback(val);
		}
	};


	struct IdentifierUnit : ExprUnit
	{
		std::string val;

		IdentifierUnit(std::string val_): val(std::move(val_)){}

		void accept(Accumulator* acc) override
		{
			acc->writeback(val);
		}
	};


	struct BinaryOpUnit : ExprUnit
	{
		std::string op;
		ExprUnit* lhs;
		ExprUnit* rhs;

		BinaryOpUnit(std::string op_, ExprUnit* lhs_, ExprUnit* rhs_): op(std::move(op_)), lhs(lhs_), rhs(rhs_){}

		~BinaryOpUnit()
		{
			delete lhs;
			delete rhs;
		}

		void accept(Accumulator* acc) override
		{
			acc->writeback("(");
			lhs->accept(acc);
			acc->writeback(op);
			rhs->accept(acc);
			acc->writeback(")");
		}
	};


	struct UnaryOpUnit : ExprUnit
	{
		std::string op;
		ExprUnit* expr;
		bool prefix;

		UnaryOpUnit(std::string op_, ExprUnit* expr_, bool prefix_): op(std::move(op_)), expr(expr_), prefix(prefix_){}

		~UnaryOpUnit()
		{
			delete expr;
		}

		void accept(Accumulator* acc) override
		{
			if (prefix) acc->writeback(op);
			acc->writeback("(");
			expr->accept(acc);
			acc->writeback(")");
			if (!prefix) acc->writeback(op);
		}
	};


	struct CallUnit : ExprUnit
	{
		std::string callee;
		std::vector<ExprUnit*> args;

		CallUnit(std::string callee_, std::vector<ExprUnit*>&& args_): callee(callee_), args(args_) {} 

		~CallUnit()
		{
			for (auto& a: args)
			{
				delete a;
			}
		}

		void accept(Accumulator* acc) override
		{
			acc->writeback(callee);
			acc->writeback("(");
			for (size_t i = 0; i < args.size(); i++)
			{
				args[i]->accept(acc);
				if (i + 1 < args.size())
				{
					acc->writeback(",");
				}
					
			}
			acc->writeback(")");
		}
	};


		struct FuncDeclUnit : Unit
	{
		std::string return_type;
		std::string name;
		std::vector<DeclUnit*> parameters;
		bool semicolon = true;

		FuncDeclUnit(std::string return_type_, std::string name_, std::vector<DeclUnit*> params_): 
			return_type(std::move(return_type_)),
			name(std::move(name_)),
			parameters(params_)
		{}

		~FuncDeclUnit()
		{
			for (auto p : parameters)
			{
				delete p;
			}
		}

		void accept(Accumulator* acc)
		{
			acc->writeback(return_type);
			acc->writeback(" ");
			acc->writeback(name);
			acc->writeback("(");
			for (size_t i = 0; i < parameters.size(); i++)
			{
				parameters[i]->accept(acc);
				if (i + 1 < parameters.size())
					acc->writeback(",");
			}
			acc->writeback(")");

			if (semicolon) {acc->writeback(";");}
		}

	};

	struct FuncDefUnit : Unit
	{
		FuncDeclUnit* decl;
		BlockUnit* code;

		FuncDefUnit(FuncDeclUnit* decl_, BlockUnit* code_): 
		decl(std::move(decl_)),
		code(code_)
		{
		}

		~FuncDefUnit()
		{
			delete decl;
			delete code;
		}

		void accept(Accumulator* acc)
		{
			decl->semicolon = false;
			decl->accept(acc);
			code->accept(acc);
		}
	};

	struct StructDeclUnit;
	struct StructDefUnit;

	struct DirectiveUnit : Unit
	{
		std::string name;
		std::string body;

		DirectiveUnit(std::string name_, std::string body_): name(name_), body(body_) {}

		~DirectiveUnit() = default;

		void accept(Accumulator* acc)
		{
			acc->writeback("#");
			acc->writeback(name);
			acc->writeback(" ");
			acc->writeback(body);
			acc->writeback("\n");
		}
	};

}
