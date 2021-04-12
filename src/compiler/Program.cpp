#include <iostream>
#include <sstream>
#include <thread>

// #define COMPILE_MULTITHREADED
#define HIDE_PRINTS

#include "compiler/BasicBlock.h"
#include "compiler/Program.h"
#include "parser/ASTNode.h"
#include "parser/StructNode.h"
#include "util/Util.h"

// #define SINGLE_FUNCTION "@find_free_block"

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
					functions.emplace(*node->lexerInfo, new Function(*this, *node));
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

	Program::~Program() {
		for (std::pair<const std::string, Function *> &pair: functions)
			delete pair.second;
	}

	void Program::compile() {
#ifdef COMPILE_MULTITHREADED
		std::vector<std::thread> threads;
		threads.reserve(functions.size());

		for (std::pair<const std::string, Function *> &pair: functions) {
			threads.emplace_back(std::thread([&]() {
				pair.second->compile();
			}));
		}

		for (std::thread &thread: threads)
			thread.join();
#else
		for (std::pair<const std::string, Function *> &pair: functions) {
#ifdef SINGLE_FUNCTION
			if (*pair.second->name == SINGLE_FUNCTION)
#endif
				pair.second->compile();
		}
#endif
	}

	std::string Program::toString() {
		std::stringstream out;
		out << "#meta\n";
		out << "name: \"" << Util::escape(sourceFilename.empty()? "Program" : sourceFilename) << "\"\n";
		out << "\n#data\n";
		dataSection(out);
		out << "\n#code\n\n";
		if (functions.count("@main") == 1)
			out << ":: main\n<halt>\n\n";
		for (std::pair<const std::string, Function *> &pair: functions) {
#ifdef HIDE_PRINTS
			if (pair.first != "@prc" && pair.first != "@prd" && pair.first != "@strprint")
#endif
			out << pair.second->toString() << "\n";
		}
		return out.str();
	}

	void Program::dataSection(std::ostream &out) {
		for (const std::pair<const std::string, GlobalVarDef *> &pair: globals) {
			const std::string name = pair.first.substr(1);
			GlobalVarDef *global = pair.second;
			ConstantPtr constant = global->constant;

			if (global->linkage == Linkage::External)
				continue;

			if (!constant) {
				warn() << name << " inexplicably lacks a constant: " << global->debugExtra() << "\n";
				continue;
			}

			ValuePtr value = constant->value;
			if (value) {
				ValueType type = value->valueType();
				if (type == ValueType::CString)
					out << name << ": \"" << dynamic_cast<CStringValue *>(value.get())->reescape() << "\"\n";
				else if (type == ValueType::Zeroinitializer || type == ValueType::Null)
					out << name << ": (" << (constant->type->width() / 8) << ")\n";
				else if (type == ValueType::Int)
					out << name << ": " << dynamic_cast<IntValue *>(value.get())->value << "\n";
				else
					error() << "Unsupported global value: " << *value << "\n";
			} else {
				out << name << "\n";
			}

		}
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
		for (std::pair<const std::string, Function *> &pair: functions) {
#ifdef SINGLE_FUNCTION
			if (*pair.second->name == SINGLE_FUNCTION)
#endif
				pair.second->debug();
		}
	}
}