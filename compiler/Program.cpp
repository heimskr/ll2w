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
				// default: node->debug();
			}
		}
	}	

	void Program::debug() const {
		for (const std::pair<std::string, Function> &pair: functions) {
			std::cout << "\e[1m" << pair.first << "\e[0m() {\n";
			pair.second.debug();
			std::cout << "}\n\n";
		}
	}
}