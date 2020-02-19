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
			const std::string *name;
			StructShape shape = StructShape::Default;
			StructForm form = StructForm::Struct;
			std::vector<Type *> types;

			StructNode(std::initializer_list<Type *>  types_, StructShape shape_);
			StructNode(const     std::vector<Type *> &types_, StructShape shape_);

			StructNode(StructShape, ASTNode *left, ASTNode *types_);
			StructNode(StructShape, ASTNode *types_);
			~StructNode();

			std::string typeStr() const;
			virtual std::string debugExtra() const override;
			virtual std::string style() const override { return "\e[33m"; }
			StructNode * copy() const;
	};
}

#endif
