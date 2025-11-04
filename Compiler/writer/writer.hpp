#include <string>
#include <vector>

#include "CuteByte.h"

#include "../parser/node.hpp"


class ByteCodeWriter
{
	Node* root;
	ctProgramImage img;
	std::string outfile;

	std::vector<ctInstrSize> instructions;

	void recurseNode(Node* node);
	void logToFile(std::string msg);

	public:

	void setOutFile(std::string filepath);
	void write(Node* root);
};