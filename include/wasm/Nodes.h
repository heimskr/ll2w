#pragma once

#include "parser/ASTNode.h"

namespace LL2W {
	enum class WASMNodeType {R};

	struct WASMBaseNode: public ASTNode {
		using ASTNode::ASTNode;
		virtual WASMNodeType nodeType() const = 0;
	};

	struct RNode: public WASMBaseNode {
		const std::string *rs, *oper, *rt, *rd;
		bool isUnsigned;
		
		RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_);
		WASMNodeType nodeType() const override { return WASMNodeType::R; }
		std::string debugExtra() const override;
	};
}
