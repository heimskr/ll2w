#ifndef PARSER_CONSTANT_H_
#define PARSER_CONSTANT_H_

#include <unordered_set>

#include "Enums.h"
#include "Types.h"
#include "Values.h"

namespace LL2W {
	class ASTNode;
	struct Constant {
		Type *type;
		Value *value;
		std::unordered_set<ParAttr> parattrs;
		int dereferenceable = -1;

		Constant() = delete;
		Constant(const Constant &) = delete;
		Constant(ASTNode *);
		~Constant();
		operator std::string() const;
	};
}

#endif
