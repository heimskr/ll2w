#pragma once

#include <initializer_list>
#include <vector>

#include "ASTNode.h"
#include "Enums.h"
#include "Types.h"
#include "util/Makeable.h"

namespace LL2W {
	class StructNode: public ASTNode, public Makeable<StructNode> {
		private:
			void addTypes(ASTNode *);

		public:
			const std::string *name = nullptr;
			StructShape shape = StructShape::Default;
			StructForm form = StructForm::Struct;
			std::vector<TypePtr> types;

			StructNode(std::initializer_list<TypePtr>  , StructShape);
			StructNode(const     std::vector<TypePtr> &, StructShape);
			StructNode(StructShape);

			StructNode(StructShape, ASTNode *left, ASTNode *types_);
			StructNode(StructShape, ASTNode *types_);

			std::string typeString() const;
			std::string typeStringPlain() const;
			virtual std::string debugExtra() const override;
			virtual std::string style() const override { return "\e[33m"; }
			std::shared_ptr<StructNode> copy() const;
	};
}
