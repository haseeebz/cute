#include "../spec/node.hpp"
#include <stack>


class CtResolver : CtNodeWalker<void>
{
    void handleRoot(CtNode::RootProgram *node);
	void handleSource(CtNode::Source *node);

	void handleFunction(CtNode::Function *node);
	void handleContainer(CtNode::Container *node);

	void handleStmtBlock(CtNode::StmtBlock *node);
	void handleDeclaration(CtNode::Declaration *node);
	void handleIf(CtNode::If *node);
	void handleLoop(CtNode::Loop *node);
	void handleWhile(CtNode::While *node);
	void handleFor(CtNode::For *node);
	void handleOut(CtNode::Out *node);
	void handleEscape(CtNode::Escape *node);

	void handleInt(CtNode::Int *node);
	void handleFloat(CtNode::Float *node);
	void handleBool(CtNode::Bool *node);
	void handleBinaryOp(CtNode::BinaryOp *node);
	void handleIdentifier(CtNode::Identifier *node);
	void handleFunctionCall(CtNode::FunctionCall *node);
	void handleAssignment(CtNode::Assignment *node);


    CtScope* currentScope;

    public:

    void resolve(CtNode::RootProgram* root);
};