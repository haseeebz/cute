#include <stdint.h>
#include <string>

#pragma once 


// Node definition

struct ctNode;

struct ctIntNode;
struct ctFloatNode;
struct ctBinaryOpNode;
struct ctIdentifierNode;


struct ctNodeVisitor
{
	virtual void visit(ctIntNode* node);
	virtual void visit(ctFloatNode* node);
	virtual void visit(ctBinaryOpNode* node);
	virtual void visit(ctIdentifierNode* node);
};


struct ctNode
{
	virtual void accept(ctNodeVisitor* visitor) = 0;
	virtual ~ctNode() = default;
};



// Node types

struct ctIntNode : public ctNode
{
	std::string raw;

	ctIntNode(std::string raw) : raw(raw) {};
	void accept(ctNodeVisitor* visitor) {visitor->visit(this);}
};


struct ctFloatNode : public ctNode
{
	std::string raw;

	ctFloatNode(std::string raw) : raw(raw) {};
	void accept(ctNodeVisitor* visitor) {visitor->visit(this);}
};


struct ctBinaryOpNode : public ctNode
{
	char op;
	ctNode* lhs;
	ctNode* rhs;

	ctBinaryOpNode(char op, ctNode* lhs, ctNode* rhs) : op(op), lhs(lhs), rhs(rhs) {};
	~ctBinaryOpNode() {delete lhs; delete rhs;}

	void accept(ctNodeVisitor* visitor) {visitor->visit(this);}
};


struct ctIdentifierNode : public ctNode
{
	std::string val;

	ctIdentifierNode(std::string val): val(val) {};

	void accept(ctNodeVisitor* visitor) {visitor->visit(this);}
};


// Visitors

struct PrintVisitor: public ctNodeVisitor
{
	uint depth = 0;
	void printDepth();

	void visit(ctIntNode* node);
	void visit(ctFloatNode* node);
	void visit(ctBinaryOpNode* node);
	void visit(ctIdentifierNode* node);
};