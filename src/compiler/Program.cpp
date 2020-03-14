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
				if (!struct_node)
					throw std::runtime_error("struct_node is null in Program::Program");
				StructType::knownStructs.emplace(*struct_node->name, std::make_shared<StructType>(struct_node));
			}
		}

		for (ASTNode *node: root) {
			switch (node->symbol) {
				case FUNCTION_DEF:
					functions.emplace(*node->lexerInfo, Function(*this, *node));
					break;
				case TOK_DECLARE: {
					ASTNode *header = node->at(0);
					declarations.emplace(header->lexerInfo->substr(1), dynamic_cast<FunctionHeader *>(header));
					break;
				}
				case TOK_SOURCE_FILENAME:
					sourceFilename = node->extractName();
					break;
				case GLOBAL_DEF:
					if (GlobalVarDef *global = dynamic_cast<GlobalVarDef *>(node)) {
						globals.emplace(*node->lexerInfo, global);
					} else throw std::runtime_error("Node with token GLOBAL_DEF isn't an instance of GlobalVarDef");
					break;
			}
		}
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