#include "../node/node.hpp"

#include "name_resolver.hpp"
#include "type_checker.hpp"

#include "analyzer.hpp"


CtNode::RootProgram*  CtAnalyzer::analyze(CtNode::RootProgram* root)
{
	root = this->resolver.analyze(root);
	root = this->typeChecker.analyze(root);
	return root;
}
