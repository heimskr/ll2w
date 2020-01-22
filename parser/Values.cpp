#include <sstream>

#include "ASTNode.h"
#include "Parser.h"
#include "Types.h"
#include "Values.h"
#include "Lexer.h"
#include "StringSet.h"

namespace LL2W {
	VectorValue::VectorValue(const ASTNode *node) {
		for (auto iter = node->cbegin(); iter != node->cend(); ++iter)
			values.push_back({getType((*iter)->at(0)), getValue((*iter)->at(1))});
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

	RegisterValue::RegisterValue(const ASTNode *node) {
		name = node->lexerInfo->at(0) == '%'? StringSet::intern(node->lexerInfo->substr(1)) : node->lexerInfo;
	}

	Value * getValue(const ASTNode *node) {
		switch (node->symbol) {
			case TOK_FLOATING: return new DoubleValue(node);
			case TOK_DECIMAL:  return new IntValue(node);
			case TOK_BOOL:     return new BoolValue(node);
			case VECTOR:       return new VectorValue(node);
			case TOK_PVAR:     return new RegisterValue(node);
			default: throw std::invalid_argument("Couldn't create Value from a node with symbol " +
			                                     std::string(Parser::getName(node->symbol)));
		}
	}
}
