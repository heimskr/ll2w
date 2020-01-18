#ifndef PARSER_FUNCTIONARGS_H_
#define PARSER_FUNCTIONARGS_H_

#include <unordered_set>
#include <vector>

#include "ASTNode.h"
#include "Types.h"

namespace LL2W {
	class FunctionArgument {
		private:
			FunctionArgument(Type *type_, const std::string *name_): type(type_), name(name_) {}
			FunctionArgument(Type *type_, const std::string &name_);

		public:
			Type *type;
			std::unordered_set<ParAttr> parattrs;
			const std::string *name;
			const std::string *originalName = nullptr;

			FunctionArgument(ASTNode *);
			~FunctionArgument() { delete type; }
	};

	struct FunctionArgs: public ASTNode {
		bool ellipse;
		std::vector<FunctionArgument> arguments;
		FunctionArgs(ASTNode *list, bool ellipse_);
	};
}

#endif
