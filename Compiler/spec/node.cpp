#include "node.hpp"

CtNode::RootProgram::~RootProgram()
{
	delete this->src;
}


CtNode::Source::~Source()
{
	for (auto func: this->functions)
	{
		delete func.second;
	}
}


CtNode::Function::~Function()
{
	for (auto para: this->parameters) {delete para;}
	delete this->block;
	delete this->scope;
	delete this->info;
}

CtNode::Container::~Container()
{
	for (auto m: this->methods) {delete m;}
	for (auto f: this->fields) {delete f;}
	delete this->scope;
	delete this->info;
}


CtNode::StmtBlock::~StmtBlock()
{
	for (auto stmt: this->stmts)
	{
		delete stmt;
	}
}


CtNode::Out::~Out()
{
	delete this->expr;
}


CtNode::Declaration::~Declaration()
{
	delete this->val;
}

CtNode::Loop::~Loop()
{
	delete this->block;
}

CtNode::If::~If()
{
	delete this->condition;
	delete this->then_block;
	delete this->else_stmt;
}


CtNode::Assignment::~Assignment()
{
	delete this->name;
	delete this->value;
}


CtNode::ExprStatment::~ExprStatment()
{
	delete this->expr;
}


CtNode::BinaryOp::~BinaryOp()
{
	delete this->left;
	delete this->right;
}


CtNode::FunctionCall::~FunctionCall()
{
	for (auto arg: this->args) {delete arg;}
}


CtNode::TypeCast::~TypeCast()
{
	delete this->expr;
}





// Printer Implementation. Mainly used for debugging.

void CtNodePrinter::print(CtNode::Base *node)
{
	this->indent = 0;
	this->walk(node);
}


void CtNodePrinter::printIndent()
{
	for (int i = 0; i < this->indent; i++)
	{
		std::cout << "   ";
	}
}


void CtNodePrinter::handleRoot(CtNode::RootProgram *node)
{
	std::cout << "(Root Node)\n";

	this->walk(node->src);
}


void CtNodePrinter::handleSource(CtNode::Source *node)
{
	std::cout << "(Source Node)\n";
	std::cout << "Function Count: " << node->functions.size() << "\n\n";

	for (auto func: node->functions)
	{
		this->walk(func.second);
	}
}


void CtNodePrinter::handleFunction(CtNode::Function *node)
{
	std::cout << "(Function Node)\n";
	std::cout << "Function Identifier: " << node->name << "\n";
	std::cout << "Parameters: \n";
	
	for (uint i = 0; i < node->parameters.size(); i++)
	{
		std::cout << i << ": ";
		this->walk(node->parameters[i]);
	}

	std::cout << "\nStatements:\n\n";
	this->indent++;
	this->walk(node->block);
	this->indent--;
}

void CtNodePrinter::handleStmtBlock(CtNode::StmtBlock *node)
{
	for (auto stmt: node->stmts)
	{
		this->walk(stmt);
		std::cout << "\n";
	}
}


void CtNodePrinter::handleDeclaration(CtNode::Declaration *node)
{
	this->printIndent();
	std::cout << "(Declaration\n";

	this->printIndent();
	std::cout << "id = " << node->name << "\n";

	this->printIndent();
	std::cout << "typeid = " << node->type_id << "\n";

	if (node->val)
	{
		this->printIndent();
		std::cout << "value = \n";

		this->indent++;
		this->walk(node->val);
		this->indent--;
	}
	

	this->printIndent();
	std::cout<< ")\n";
}


void CtNodePrinter::handleOut(CtNode::Out *node)
{
	this->printIndent();
	std::cout << "(Out\n";

	this->printIndent();
	std::cout << "expr = \n";

	this->indent++;
	this->walk(node->expr);
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleLoop(CtNode::Loop *node)
{
	this->printIndent();
	std::cout << "(Loop\n";

	this->printIndent();
	std::cout << "block = \n";

	this->indent++;
	this->walk(node->block);
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}

void CtNodePrinter::handleWhile(CtNode::While *node)
{
	this->printIndent();
	std::cout << "(While\n";

	this->printIndent();
	std::cout << "condition = \n";
	this->indent++;
	this->walk(node->condition);
	this->indent--;

	this->printIndent();
	std::cout << "statements = \n";
	this->indent++;
	this->walk(node->block);
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleFor(CtNode::For *node)
{
	this->printIndent();
	std::cout << "(For\n";

	this->printIndent();
	std::cout << "init = \n";
	this->indent++;
	this->walk(node->init);
	this->indent--;

	this->printIndent();
	std::cout << "condition = \n";
	this->indent++;
	this->walk(node->condition);
	this->indent--;

	this->printIndent();
	std::cout << "step = \n";
	this->indent++;
	this->walk(node->step);
	this->indent--;

	this->printIndent();
	std::cout << "statements = \n";
	this->indent++;
	this->walk(node->block);
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleIf(CtNode::If *node)
{
	this->printIndent();
	std::cout << "(If\n";

	this->printIndent();
	std::cout << "condition =\n";
	this->indent++;
	this->walk(node->condition);
	this->indent--;

	this->printIndent();
	std::cout << "then =\n";
	this->indent++;
	this->walk(node->then_block);
	this->indent--;

	this->printIndent();
	std::cout << "else = \n";
	this->indent++;
	if (node->else_stmt) {this->walk(node->else_stmt);}
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
};

void CtNodePrinter::handleEscape(CtNode::Escape *node)
{
	this->printIndent();
	std::cout << "(Escape\n";
	this->indent++;
	std::cout << node->code << std::endl;
	this->indent--;
	this->printIndent();
	std::cout << ")\n";
}

void CtNodePrinter::handleAssignment(CtNode::Assignment *node)
{
	this->printIndent();
	std::cout << "(Assignement \n";

	this->printIndent();
	std::cout <<  " variable= " << node->name->val;
	std::cout <<  " value = \n";
	this->indent++;
	this->walk(node->value);
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleInt(CtNode::Int *node)
{
	this->printIndent();
	std::cout << "(Int " << node->raw << ")\n";
}


void CtNodePrinter::handleFloat(CtNode::Float *node)
{
	this->printIndent();
	std::cout << "(Float " << node->raw << ")\n";
}


void CtNodePrinter::handleBool(CtNode::Bool *node)
{
	this->printIndent();
	std::cout << "(Bool " << node->val << ")\n";
}

void CtNodePrinter::handleBinaryOp(CtNode::BinaryOp *node)
{
	this->printIndent();
	std::cout << "(BinaryOp \n";
	this->indent++;

	this->printIndent();
	std::cout << "op= " << (int)node->op << "\n";
	this->walk(node->left);
	this->walk(node->right);

	this->indent--;
	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleIdentifier(CtNode::Identifier *node)
{
	this->printIndent();
	std::cout << "(Identifier " << node->val << ")\n";
}


void CtNodePrinter::handleFunctionCall(CtNode::FunctionCall *node)
{
	this->printIndent();
	std::cout << "(FunctionCall\n";

	this->printIndent();
	std::cout << "name = " << node->name << "\n";
	
	this->printIndent();
	std::cout << "args = \n";
	this->indent++;
	for (auto args: node->args) {this->walk(args);}
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}


void CtNodePrinter::handleTypeCast(CtNode::TypeCast *node)
{
	this->printIndent();
	std::cout << "(TypeCast\n";

	this->printIndent();
	std::cout << "type = " << node->to_type << "\n";

	this->printIndent();
	std::cout << "expr = \n";
	this->indent++;
	this->walk(node->expr);
	this->indent--;

	this->printIndent();
	std::cout << ")\n";
}

