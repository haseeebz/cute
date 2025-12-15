#include "../node/node.hpp"

#include "name_resolver.hpp"

#pragma once


class CtAnalyzer
{
	CtNameResolver resolver;

	public:

	CtNode::RootProgram* analyze(CtNode::RootProgram* root);
};