#include "../spec/node.hpp"
#include "../codegen/node.hpp"

class CtTranspiler : CtNodeWalker<CtGenNode::Base*>
{
    CtGenNode::Root* handleRoot(CtNode::RootProgram *node);
	CtGenNode::Source* handleSource(CtNode::Source *node);

	CtGenNode::Function* handleFunction(CtNode::Function *node);
	CtGenNode::Struct* handleContainer(CtNode::Container *node);

	CtGenNode::StmtBlock* handleStmtBlock(CtNode::StmtBlock *node);
	CtGenNode::Declaration* handleDeclaration(CtNode::Declaration *node);
	CtGenNode::If* handleIf(CtNode::If *node);
	CtGenNode::While* handleLoop(CtNode::Loop *node);
	CtGenNode::While* handleWhile(CtNode::While *node);
	CtGenNode::For* handleFor(CtNode::For *node);
	CtGenNode::Call* handleOut(CtNode::Out *node);
	CtGenNode::StmtBlock* handleEscape(CtNode::Escape *node);

	CtGenNode::Literal* handleInt(CtNode::Int *node);
	CtGenNode::Literal* handleFloat(CtNode::Float *node);
	CtGenNode::Literal* handleBool(CtNode::Bool *node);
	CtGenNode::BinaryOp* handleBinaryOp(CtNode::BinaryOp *node);
	CtGenNode::UnaryOp* handleUnaryOp(CtNode::UnaryOp *node);
	CtGenNode::Identifier* handleIdentifier(CtNode::Identifier *node);
	CtGenNode::Call* handleFunctionCall(CtNode::FunctionCall *node);
	CtGenNode::Assignment* handleAssignment(CtNode::Assignment *node);

    public:

    CtGenNode::Root* transpile(CtNode::RootProgram* root);
};