#include <iostream>

#include "parser/ASTNode.h"
#include "compiler/BasicBlock.h"
#include "compiler/Program.h"

namespace LL2W {
	Program::Program(const ASTNode &root) {
		for (const ASTNode *node: root) {
			switch (node->symbol) {
				case FUNCTION_DEF:
					functions.emplace(*node->lexerInfo, Function(*node));
					break;
				case TOK_SOURCE_FILENAME:
					sourceFilename = node->extractName();
					break;
				// default: node->debug();
			}
		}

		// for (const std::pair<std::string, Function> &pair: functions) {

		// }
	}	

	void Program::debug() const {
		for (const std::pair<std::string, Function> &pair: functions) {
			std::cout << "\e[1m" << pair.first << "\e[0m(";
			std::vector<FunctionArgument> &args = pair.second.arguments->arguments;
			for (auto begin = args.begin(), iter = begin, end = args.end(); iter != end; ++iter) {
				if (iter != begin)
					std::cout << "\e[2m,\e[0m ";
				std::cout << *iter->type;
				if (iter->name)
					std::cout << " " << *iter->name;
			}
			std::cout << ") {\n";
			pair.second.debug();
			std::cout << "}\n\n";
		}
	}
}