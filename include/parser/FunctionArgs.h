#pragma once

#include <unordered_set>
#include <vector>

#include "ASTNode.h"
#include "Types.h"

namespace LL2W {
	class FunctionArgument {
		public:
			TypePtr type;
			std::unordered_set<ParAttr> parattrs;
			const std::string *name = nullptr;
			const std::string *originalName = nullptr;

			FunctionArgument(TypePtr type_, const std::string *name_): type(type_), name(name_) {}
			FunctionArgument(TypePtr type_, const std::string &name_);
			FunctionArgument(ASTNode *);
	};

	struct FunctionArgs: public ASTNode {
		bool ellipsis;
		std::vector<FunctionArgument> arguments;
		FunctionArgs(ASTNode *list, bool ellipsis_);
	};
}
