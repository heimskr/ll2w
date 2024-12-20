#include <iostream>

#include "parser/FunctionArgs.h"
#include "parser/StringSet.h"
#include "parser/Enums.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"

namespace LL2W {
	FunctionArgument::FunctionArgument(TypePtr type_, const std::string &name_):
		type(type_), name(StringSet::intern(name_)) {}

	FunctionArgs::FunctionArgs(bool ellipsis):
		ellipsis(ellipsis) {}

	FunctionArgs::FunctionArgs(ASTNode *list, bool ellipsis):
		ASTNode(llvmParser, LLVM_FUNCTION_ARGS, ""), ellipsis(ellipsis) {
			if (list) {
				arguments.reserve(list->size());
				for (ASTNode *child: list->children)
					arguments.emplace_back(child);
				delete list;
			}
		}

	FunctionArgument::FunctionArgument(ASTNode *node):
		type(getType(node)) {
			// Each function argument node can have PARATTR_LIST and TOK_PVAR/TOK_PSTRING children at the end.
			for (ASTNode *child: node->children) {
				if (child->symbol == LLVMTOK_PVAR) {
					name = StringSet::intern(child->extractName());
					originalName = child->lexerInfo;
				} else if (child->symbol == LLVM_PARATTR_LIST) {
					for (ASTNode *parattr_node: child->children) {
						const std::string &pname = *parattr_node->lexerInfo;
						for (const std::pair<const ParAttr, std::string> &pair: parattr_map) {
							if (pname == pair.second) {
								parattrs.insert(pair.first);
								break;
							}
						}
					}
				}
			}
		}
}
