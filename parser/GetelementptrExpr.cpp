#include <cstdlib>
#include "GetelementptrExpr.h"

namespace LL2W {
	GetelementptrExpr::GetelementptrExpr(const ASTNode *inbounds_, const ASTNode *type_, const ASTNode *ptr_type,
			                             const ASTNode *variable_, const ASTNode *decimal_list): GetelementptrExpr() {
		if (inbounds_) {
			inbounds = true;
			delete inbounds_;
		}

		type = getType(type_);
		delete type_;

		ptrType = getType(ptr_type);
		delete ptr_type;

		variable = getValue(variable_);
		delete variable_;

		for (auto iter = decimal_list->cbegin(), end = decimal_list->cend(); iter != end; ++iter) {
			const ASTNode *comma = *iter;
			const ASTNode *inttype = comma->at(0);
			const ASTNode *decimal = comma->at(1);
			decimals.push_back({atoi(inttype->lexerInfo->substr(1).c_str()), atol(decimal->lexerInfo->c_str())});
		}
		delete decimal_list;
	}

	GetelementptrExpr::~GetelementptrExpr() {
		delete type;
		delete ptrType;
		delete variable;
	}
}