#ifndef PARSER_GETELEMENTPTREXPR_H_
#define PARSER_GETELEMENTPTREXPR_H_

#include <utility>
#include <vector>

#include "ASTNode.h"
#include "Types.h"
#include "Values.h"
#include "Lexer.h"

namespace LL2W {
	class GetelementptrExpr: public ASTNode {
		private:
			GetelementptrExpr(const std::string *str): ASTNode(GETELEMENTPTR_EXPR, str) {}
			GetelementptrExpr(): ASTNode(GETELEMENTPTR_EXPR, "") {}

		public:
			bool inbounds = false;
			Type *type, *ptrType;
			Value *variable;
			std::vector<std::pair<int, long>> decimals {};

			GetelementptrExpr(const ASTNode *inbounds_, const ASTNode *type_, const ASTNode *ptr_type,
			                  const ASTNode *variable_, const ASTNode *decimal_list);
			~GetelementptrExpr();
	};
}

#endif
