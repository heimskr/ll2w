#ifndef PARSER_STRUCT_H_
#define PARSER_STRUCT_H_

#include <initializer_list>
#include <vector>

#include "ASTNode.h"
#include "Enums.h"
#include "Types.h"

namespace LL2W {
	struct StructNode: public ASTNode {
		const std::string *name;
		StructShape shape = StructShape::Default;
		StructForm form = StructForm::Struct;
		std::vector<Type *> types;

		StructNode(): ASTNode(STRUCTDEF, "") {}
		StructNode(std::initializer_list<Type *>  types_, StructShape shape_):
			ASTNode(STRUCTDEF, ""), shape(shape_), types(types_) {}
		StructNode(const     std::vector<Type *> &types_, StructShape shape_):
			ASTNode(STRUCTDEF, ""), shape(shape_), types(types_) {}

		StructNode(StructShape, ASTNode *left, ASTNode *types_);
		StructNode(StructShape, ASTNode *types_);

		virtual std::string debugExtra() override;
		virtual std::string style() const override { return "\e[33m"; }
	};
}

#endif