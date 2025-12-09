#include "CuteCompiler.hpp"

#include <string>

#include "internals.hpp"
#include "CuteToken.hpp"
#include "node/node.hpp"
#include "node/walker.hpp"


using namespace Node;

void CuteCompiler::compile(std::string filepath, std::string outfile)
{	
	auto* root = new RootProgram();
    root->src = new Source();

    // Function
    auto* fn = new Function();
    fn->name = new Identifier("main");

    // ----- Statement 1 -----
    // int a;
    auto* declA = new Declaration();
    declA->type = new Identifier("int");
    declA->name = new Identifier("a");
    fn->statements.push_back(declA);

    // ----- Statement 2 -----
    // a = (5 + 3);
    auto* assignA = new Assignment();
    assignA->name = new Identifier("a");

    auto* expr5 = new Int("5");
    auto* expr3 = new Int("3");

    auto* addExpr = new BinaryOp(BinaryOp::Type::Add, expr5, expr3);
    assignA->value = addExpr;

    fn->statements.push_back(assignA);

    // ----- Statement 3 -----
    // int b;2
    // b = a;
    auto* declB = new Declaration();
    declB->type = new Identifier("int");
    declB->name = new Identifier("b");
    fn->statements.push_back(declB);

    auto* assignB = new Assignment();
    assignB->name = new Identifier("b");
    assignB->value = new Identifier("a");
    fn->statements.push_back(assignB);

    // Stuff the function in the source
    root->src->functions.push_back(fn);

	NodePrinter printer;
	printer.walk(root);
	delete root;
}


