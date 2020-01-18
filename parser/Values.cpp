#include <sstream>

#include "ASTNode.h"
#include "Parser.h"
#include "Types.h"
#include "Values.h"
#include "yyparse.h"

namespace LL2W {
	VectorValue::VectorValue(ASTNode *node) {
		for (ASTNode *comma: *node)
			values.push_back({getType(comma->at(0)), getValue(comma->at(1))});
	}

	VectorValue::~VectorValue() {
		for (const std::pair<Type *, Value *> &pair: values) {
			delete pair.first;
			delete pair.second;
		}
	}

	Value * VectorValue::copy() const {
		std::vector<std::pair<Type *, Value *>> newvec {};
		for (const std::pair<Type *, Value *> &pair: values)
			newvec.push_back({pair.first->copy(), pair.second->copy()});
		return new VectorValue(newvec);
	}

	VectorValue::operator std::string() {
		std::stringstream out;
		out << "\e[2m<\e[0m";
		auto begin = values.cbegin();
		for (auto iter = begin, end = values.cend(); iter != end; ++iter) {
			const std::pair<Type *, Value *> &pair = *iter;
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << std::string(*pair.first) << " " << std::string(*pair.second);
		}
		out << "\e[2m>\e[0m";
		return out.str();
	}

	Value * getValue(ASTNode *node) {
		switch (node->symbol) {
			case TOK_FLOATING: return new DoubleValue(node->lexerInfo);
			case TOK_DECIMAL:  return new IntValue(node->lexerInfo);
			case VECTOR:       return new VectorValue(node);
			default: throw std::invalid_argument("Couldn't create Value from a node with symbol " +
			                                     std::string(Parser::getName(node->symbol)));
		}
	}
}
