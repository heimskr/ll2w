#include <iostream>

#include "ASTNode.h"
#include "Constant.h"
#include "Lexer.h"

namespace LL2W {
	Constant::Constant(ASTNode *node) {
		if (node->symbol != CONSTANT)
			throw std::runtime_error("Constant::Constant: node doesn't have symbol CONSTANT");
		type = getType(node->at(0));
		
		ASTNode *value_node = node->at(2);
		if (GetelementptrValue *gep_value = dynamic_cast<GetelementptrValue *>(value_node)) {
			value = gep_value;
			std::cout << "gep: " << value << "\n";
		} else {
			value = getValue(value_node);
			std::cout << "From getValue: " << value << "\n";
		}

		for (ASTNode *child: *node->at(1)) {
			if (child->symbol == TOK_DEREF) {
				dereferenceable = atoi(child->at(0)->lexerInfo->c_str());
			} else {
				for (const std::pair<ParAttr, std::string> &pair: parattr_map) {
					if (*child->lexerInfo == pair.second) {
						parattrs.insert(pair.first);
						break;
					}
				}
			}
		}
	}

	Constant::~Constant() {
		delete type;
		delete value;
	}
}