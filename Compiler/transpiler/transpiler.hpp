#include "../codegen/units.hpp"

#include "../node/node.hpp"


class CtTranspiler: CtNodeWalker<Codegen::Unit*>
{

	Codegen::RootUnit* handleRoot(CtNode::RootProgram *node);
	Codegen::RootUnit* handleSource(CtNode::Source *node);

	Codegen::FuncDefUnit* handleFunction(CtNode::Function *node);

	Codegen::BlockUnit* handleStmtBlock(CtNode::StmtBlock *node);
	Codegen::DeclUnit* handleDeclaration(CtNode::Declaration *node);
	Codegen::IfUnit* handleIf(CtNode::If *node);
	Codegen::WhileUnit* handleLoop(CtNode::Loop *node);
	Codegen::WhileUnit* handleWhile(CtNode::While *node);
	Codegen::ForUnit* handleFor(CtNode::For *node);
	Codegen::CallUnit* handleOut(CtNode::Out *node);

	Codegen::LiteralUnit* handleInt(CtNode::Int *node);
	Codegen::LiteralUnit* handleFloat(CtNode::Float *node);
	Codegen::LiteralUnit* handleBool(CtNode::Bool *node);
	Codegen::BinaryOpUnit* handleBinaryOp(CtNode::BinaryOp *node);
	Codegen::IdentifierUnit* handleIdentifier(CtNode::Identifier *node);
	Codegen::CallUnit* handleFunctionCall(CtNode::FunctionCall *node);
	Codegen::AssignUnit* handleAssignment(CtNode::Assignment *node);
	Codegen::Unit* handleTypeCast(CtNode::TypeCast *node);

	public:

	void transpile(CtNode::RootProgram* root, std::string outfile);
};