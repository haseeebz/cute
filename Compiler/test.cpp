#include "CuteCompiler.hpp"

#include "../codegen/units.hpp"
#include <iostream>
#include <fstream>
#include <format>
#include <vector>

void exec_test()
{
	Codegen::Accumulator acc;

	auto root = Codegen::RootUnit(
		{
			new Codegen::FuncDefUnit(
				new Codegen::FuncDeclUnit(
					"int",
					"main",
					{
					}
				),
				new Codegen::BlockUnit(
					{
						new Codegen::StmtUnit(new Codegen::DeclUnit("int", "test")),
						new Codegen::StmtUnit(
							new Codegen::BinaryOpUnit(
								"+",
								new Codegen::LiteralUnit("12"),
								new Codegen::LiteralUnit("10")
							)
						),
					}
				)
			)
		}
	);


	std::cout << acc.accumulate(root) << std::endl;
}