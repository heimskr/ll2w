#include <iostream>

#include "FunctionArgs.h"
#include "StringSet.h"

namespace LL2W {
	FunctionArgument::FunctionArgument(Type *type_, const std::string &name_):
		type(type_), name(StringSet::intern(name_)) {}

	FunctionArgs::FunctionArgs(ASTNode *list, bool ellipse_): ASTNode(FUNCTION_ARGS, ""), ellipse(ellipse_) {
		if (list) {
			arguments.reserve(list->size());
			for (ASTNode *child: list->children)
				arguments.emplace_back(child);
			delete list;
		}
	}

	FunctionArgument::FunctionArgument(ASTNode *node): type(getType(node)) {
		// Each function argument node can have PARATTR_LIST and TOK_PVAR/TOK_PSTRING children at the end.
		for (ASTNode *child: node->children) {
			if (child->symbol == TOK_PVAR || child->symbol == TOK_PSTRING) {
				name = StringSet::intern(child->extractName());
				originalName = child->lexerInfo;
			} else if (child->symbol == PARATTR_LIST) {
				for (ASTNode *parattr_node: child->children) {
					const std::string &pname = *parattr_node->lexerInfo;
					for (const std::pair<ParAttr, std::string> &pair: parattr_map) {
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
