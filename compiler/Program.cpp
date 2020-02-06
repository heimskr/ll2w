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

	void Program::extract() {
		for (std::pair<const std::string, Function> &pair: functions)
			pair.second.extract();
	}

	void Program::debug() {
		for (std::pair<const std::string, Function> &pair: functions)
			pair.second.debug();
	}
}