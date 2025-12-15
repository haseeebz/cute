#include "../node/node.hpp"

#include "name_resolver.hpp"

#include "analyzer.hpp"


CtNode::RootProgram*  CtAnalyzer::analyze(CtNode::RootProgram* root)
{
	CtNodePrinter printer;
	printer.print(root);
	root = this->resolver.analyze(root);
	return root;
}
