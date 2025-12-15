#include "../node/node.hpp"

#include "name_resolver.hpp"
#include "type_checker.hpp"

#pragma once


class CtAnalyzer
{
	CtNameResolver resolver;
	CtTypeChecker  typeChecker;

	public:

	CtNode::RootProgram* analyze(CtNode::RootProgram* root);
};