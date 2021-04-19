#pragma once

#include "parser/ASTNode.h"

namespace LL2W {
	enum class WASMNodeType {R, I, Copy, Load, Store};

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

	struct INode: public WASMBaseNode {
		const std::string *rs, *oper, *rd;
		long imm;
		bool isUnsigned;

		INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm, ASTNode *rd_, ASTNode *unsigned_);
		WASMNodeType nodeType() const override { return WASMNodeType::I; }
		std::string debugExtra() const override;
	};

	struct WASMCopyNode: public WASMBaseNode {
		const std::string *rs, *rd;
		bool isByte;

		WASMCopyNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Copy; }
		std::string debugExtra() const override;
	};

	struct WASMLoadNode: public WASMBaseNode {
		const std::string *rs, *rd;
		bool isByte;

		WASMLoadNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Load; }
		std::string debugExtra() const override;
	};

	struct WASMStoreNode: public WASMBaseNode {
		const std::string *rs, *rd;
		bool isByte;

		WASMStoreNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Store; }
		std::string debugExtra() const override;
	};
}
