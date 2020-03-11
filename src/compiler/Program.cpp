#include <iostream>

#include "parser/ASTNode.h"
#include "parser/StructNode.h"
#include "compiler/BasicBlock.h"
#include "compiler/Program.h"

namespace LL2W {
	Program::Program(const ASTNode &root) {
		// Look for all struct definitions.
		for (const ASTNode *node: root) {
			if (node->symbol == STRUCTDEF) {
				const StructNode *struct_node = dynamic_cast<const StructNode *>(node);
				StructType::knownStructs.emplace(*struct_node->name, std::make_shared<StructType>(struct_node));
			}
		}

		for (const ASTNode *node: root) {
			switch (node->symbol) {
				case FUNCTION_DEF:
					functions.emplace(*node->lexerInfo, Function(*this, *node));
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

	void Program::compile() {
		for (std::pair<const std::string, Function> &pair: functions)
			pair.second.compile();
	}

	void Program::debug() {
		for (std::pair<const std::string, Function> &pair: functions)
			pair.second.debug();
	}
}