#pragma once

#include <string>
#include <vector>

namespace CodeGen
{

    struct Unit
    {
        Unit() = default;
        virtual ~Unit() = default;

        virtual void writeback() = 0;
    };

    struct BlockUnit : Unit
    {
        std::vector<Unit*> units;

        BlockUnit() = default;
        BlockUnit(const std::vector<Unit*>& units) : units(units) {}

        void writeback();
    };


    struct IdentifierUnit : Unit
    {
        std::string name;

        IdentifierUnit(const std::string& name) : name(name) {}

        void writeback();
    };

    struct LiteralUnit : Unit
    {
        std::string value;

        LiteralUnit(const std::string& value) : value(value) {}

        void writeback();
    };


    struct TypeUnit : Unit
    {
        std::string name;
		bool is_pointer = false;

        TypeUnit(const std::string& name) : name(name) {}
		TypeUnit(const std::string& name, bool pointer) : name(name), is_pointer(pointer) {}

        void writeback();
    };


    struct DeclarationUnit : Unit
    {
        TypeUnit* type;
        std::string name;

        DeclarationUnit(TypeUnit* type, const std::string& name): type(type), name(name) {}

        void writeback();
    };


    struct UnaryOpUnit : Unit
    {
        std::string op;
        Unit* expr;
        bool postfix = false;

        UnaryOpUnit(const std::string& op, Unit* expr, bool postfix = false) : op(op), expr(expr), postfix(postfix) {}

        void writeback();
    };


    struct BinaryOpUnit : Unit
    {
        std::string op;
        Unit* lhs;
        Unit* rhs;

        BinaryOpUnit(const std::string& op, Unit* lhs, Unit* rhs) : op(op), lhs(lhs), rhs(rhs) {}

        void writeback();
    };


    struct AssignmentUnit : Unit
    {
        Unit* lhs;
        Unit* val;

        AssignmentUnit(Unit* lhs, Unit* val): lhs(lhs), val(val) {}

        void writeback();
    };


    struct CastUnit : Unit
    {
        TypeUnit* type;
        Unit* expr;

        CastUnit(TypeUnit* type, Unit* expr) : type(type), expr(expr) {}

        void writeback();
    };


    struct CallUnit : Unit
    {
        Unit* callee;
        std::vector<Unit*> args;

        CallUnit(Unit* callee, const std::vector<Unit*>& args): callee(callee), args(args) {}

        void writeback();
    };


    struct IfUnit : Unit
    {
        Unit* condition;
        BlockUnit* then_block;
        BlockUnit* else_block = nullptr;

        IfUnit(Unit* cond, BlockUnit* then_block, BlockUnit* else_block = nullptr) : 
		condition(cond), then_block(then_block), else_block(else_block) {}

        void writeback();
    };

    struct WhileUnit : Unit
    {
        Unit* condition;
        BlockUnit* body;

        WhileUnit(Unit* cond, BlockUnit* body): condition(cond), body(body) {}

        void writeback();
    };

    struct ForUnit : Unit
    {
        Unit* init;
        Unit* condition;
        Unit* step;
        BlockUnit* body;

        ForUnit(Unit* init, Unit* cond, Unit* step, BlockUnit* body) : init(init), condition(cond), step(step), body(body) {}

        void writeback();
    };


    struct BreakUnit : Unit
    {
        void writeback();
    };


    struct ContinueUnit : Unit
    {
        void writeback();
    };


    struct ReturnUnit : Unit
    {
        Unit* value = nullptr;

        ReturnUnit(Unit* value = nullptr) : value(value) {}

        void writeback();
    };



    struct FunctionDefUnit : Unit
    {
        Unit* return_type;
        std::string name;
        std::vector<TypeUnit> params;
        BlockUnit* body;

        FunctionDefUnit(
            Unit* return_type,
            const std::string& name,
            const std::vector<TypeUnit>& params,
            BlockUnit* body
        ): 
			return_type(return_type),
            name(name),
            params(params),
            body(body) {}

        void writeback();
    };

    struct FunctionDeclUnit : Unit
    {
        Unit* return_type;
        std::string name;
        std::vector<TypeUnit> params;

        FunctionDeclUnit(
            Unit* return_type,
            const std::string& name,
            const std::vector<TypeUnit>& params
        ): 
			return_type(return_type),
            name(name),
            params(params) {}

        void writeback();
    };


} 
