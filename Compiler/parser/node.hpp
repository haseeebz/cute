#include <stdint.h>
#include <string>

#pragma once 


// Node definition

struct ctNode;

struct ctIntNode;
struct ctFloatNode;
struct ctBinaryOpNode;
struct ctIdentifierNode;


struct NodeVisitor
{
	virtual void visit(ctIntNode* node) = 0; 
	virtual void visit(ctFloatNode* node) = 0;
	virtual void visit(ctBinaryOpNode* node) = 0;
	virtual void visit(ctIdentifierNode* node) = 0;

	virtual ~NodeVisitor() = default;
};


struct ctNode
{
	virtual void accept(NodeVisitor* visitor) = 0;
	virtual ~ctNode() = default;
};



// Node types

struct ctIntNode : public ctNode
{
	std::string raw;

	ctIntNode(std::string raw) : raw(raw) {};
	inline void accept(NodeVisitor* visitor) {visitor->visit(this);}
};


struct ctFloatNode : public ctNode
{
	std::string raw;

	ctFloatNode(std::string raw) : raw(raw) {};
	inline void accept(NodeVisitor* visitor) {visitor->visit(this);}
};


struct ctBinaryOpNode : public ctNode
{
	char op;
	ctNode* lhs;
	ctNode* rhs;

	ctBinaryOpNode(char op, ctNode* lhs, ctNode* rhs) : op(op), lhs(lhs), rhs(rhs) {};
	~ctBinaryOpNode() {delete lhs; delete rhs;}

	inline void accept(NodeVisitor* visitor) {visitor->visit(this);}
};


struct ctIdentifierNode : public ctNode
{
	std::string val;

	ctIdentifierNode(std::string val): val(val) {};

	inline void accept(NodeVisitor* visitor) {visitor->visit(this);}
};


// Visitors

struct PrintVisitor: public NodeVisitor
{
	uint depth = 0;
	void printDepth();

	void visit(ctIntNode* node);
	void visit(ctFloatNode* node);
	void visit(ctBinaryOpNode* node);
	void visit(ctIdentifierNode* node);

	~PrintVisitor() {};
};