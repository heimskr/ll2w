#ifndef PARSER_STRUCT_H_
#define PARSER_STRUCT_H_

#include <initializer_list>
#include <vector>

#include "ASTNode.h"
#include "Types.h"
#include "yyparse.h"

namespace LL2W {
	struct StructNode: public ASTNode {
		enum class Shape {Default, Opaque, Packed};
		const std::string *name;
		Shape shape = Shape::Default;
		std::vector<Type *> types;

		StructNode(): ASTNode(STRUCTDEF, "") {}
		StructNode(std::initializer_list<Type *>  types_, Shape shape_):
			ASTNode(STRUCTDEF, ""), shape(shape_), types(types_) {}
		StructNode(const     std::vector<Type *> &types_, Shape shape_):
			ASTNode(STRUCTDEF, ""), shape(shape_), types(types_) {}

		StructNode(Shape, ASTNode *left, ASTNode *types_);

		virtual std::string debugExtra() override;
		virtual std::string style() const override { return "\e[33m"; }
	};
}

#endif
