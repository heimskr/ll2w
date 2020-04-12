#include <iostream>
#include <sstream>
#include <thread>

// #define COMPILE_MULTITHREADED

#include "compiler/BasicBlock.h"
#include "compiler/Program.h"
#include "parser/ASTNode.h"
#include "parser/StructNode.h"
#include "util/Util.h"

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
#ifdef COMPILE_MULTITHREADED
		std::vector<std::thread> threads;
		threads.reserve(functions.size());

		for (std::pair<const std::string, Function> &pair: functions) {
			threads.emplace_back(std::thread([&]() {
				pair.second.compile();
			}));
		}

		for (std::thread &thread: threads)
			thread.join();
#else
		for (std::pair<const std::string, Function> &pair: functions)
			pair.second.compile();
#endif
	}

	std::string Program::toString() {
		std::stringstream out;
		for (std::pair<const std::string, Function> &pair: functions)
			out << pair.second.toString() << "\n";
		return out.str();
	}

	int Program::symbolSize(const std::string &name) const {
		GlobalVarDef *def = globals.at(name);
		if (def->type)
			return def->type->width();
		if (def->constant) {
			if (def->constant->type)
				return def->constant->type->width();
			throw std::runtime_error("Type is null in constant of global " + name);
		}
		throw std::runtime_error("Type and constant are both null for global " + name);
	}

	void Program::debug() {
		for (std::pair<const std::string, Function> &pair: functions)
			pair.second.debug();
	}
}