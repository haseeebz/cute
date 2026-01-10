#include "CuteCompiler.hpp"

#include "../codegen/units.hpp"
#include <iostream>
#include <fstream>
#include <format>
#include <vector>

void exec_test()
{
	Codegen::Accumulator acc;

	auto root = Codegen::RootUnit({
		// Function definition: int add(int a, int b) { return a + b; }

		new Codegen::DirectiveUnit("include", "<stdio.h>"),

		// Main function: int main() { ... }
		new Codegen::FuncDefUnit(
			new Codegen::FuncDeclUnit("int", "main", {}),
			new Codegen::BlockUnit({
				// Declare x
				new Codegen::DeclUnit("int", "x"),

				new Codegen::ForUnit(
					new Codegen::DeclUnit("int", "x", new Codegen::LiteralUnit("0")),
					new Codegen::BinaryOpUnit("<", new Codegen::IdentifierUnit("x"), new Codegen::LiteralUnit("10")),
					new Codegen::UnaryOpUnit("++", new Codegen::IdentifierUnit("x"), false),

					new Codegen::BlockUnit({
						new Codegen::CallUnit(
						"printf",
						{
							new Codegen::LiteralUnit("\"%d\\n\""),
							new Codegen::IdentifierUnit("x")
						}
						)
					})
				)
			})				
		)
	});


	std::string outfile = "test.c";
	std::ofstream stream(outfile);
	stream << acc.accumulate(&root);
	stream.close();

	std::string str = std::format("gcc {} -o program", outfile);
	std::system(str.data());
}