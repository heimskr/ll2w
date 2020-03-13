#ifndef PARSER_STRUCTNODE_H_
#define PARSER_STRUCTNODE_H_

#include <initializer_list>
#include <vector>

#include "ASTNode.h"
#include "Enums.h"
#include "Types.h"

namespace LL2W {
	class StructNode: public ASTNode {
		private:
			void addTypes(ASTNode *);

		public:
			const std::string *name = nullptr;
			StructShape shape = StructShape::Default;
			StructForm form = StructForm::Struct;
			std::vector<TypePtr> types;

			StructNode(std::initializer_list<TypePtr>  types_, StructShape shape_);
			StructNode(const     std::vector<TypePtr> &types_, StructShape shape_);

			StructNode(StructShape, ASTNode *left, ASTNode *types_);
			StructNode(StructShape, ASTNode *types_);

			std::string typeStr() const;
			virtual std::string debugExtra() const override;
			virtual std::string style() const override { return "\e[33m"; }
			std::shared_ptr<StructNode> copy() const;
	};
}

#endif
