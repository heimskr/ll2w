#pragma once

#include <variant>

#include "parser/ASTNode.h"

namespace LL2W {
	enum class WASMNodeType {
		Immediate, RType, IType, Copy, Load, Store, Set, Li, Si, Lni, Ch, Lh, Sh, Cmp, Cmpi, Sel, J, Jc, Jr, Jrc,
		SizedStack
	};

	enum class WASMCondition {None, Positive, Negative, Zero, NonZero};

	using Immediate = std::variant<long, const std::string *>;

	struct WASMBaseNode: public ASTNode {
		WASMBaseNode(int sym);
		virtual WASMNodeType nodeType() const = 0;
	};

	struct WASMImmediateNode: public WASMBaseNode {
		Immediate imm;

		WASMImmediateNode(ASTNode *);
		virtual WASMNodeType nodeType() const override { return WASMNodeType::Immediate; }
		std::string debugExtra() const override;
	};

	struct RNode: public WASMBaseNode {
		const std::string *rs, *oper, *rt, *rd;
		bool isUnsigned;
		
		RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_);
		// Used for the mv pseudoinstruction.
		RNode(ASTNode *rs_, const std::string &oper_, const std::string &rt_, ASTNode *rd_, ASTNode *unsigned_);
		WASMNodeType nodeType() const override { return WASMNodeType::RType; }
		std::string debugExtra() const override;
	};

	struct INode: public WASMBaseNode {
		const std::string *rs, *oper, *rd;
		Immediate imm;
		bool isUnsigned;

		INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm, ASTNode *rd_, ASTNode *unsigned_);
		WASMNodeType nodeType() const override { return WASMNodeType::IType; }
		std::string debugExtra() const override;
	};

	struct WASMMemoryNode: public WASMBaseNode {
		const std::string *rs, *rd;
		bool isByte;

		WASMMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
	};

	struct WASMCopyNode: public WASMMemoryNode {
		WASMCopyNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Copy; }
		std::string debugExtra() const override;
	};

	struct WASMLoadNode: public WASMMemoryNode {
		WASMLoadNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Load; }
		std::string debugExtra() const override;
	};

	struct WASMStoreNode: public WASMMemoryNode {
		WASMStoreNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Store; }
		std::string debugExtra() const override;
	};

	struct WASMSetNode: public WASMBaseNode {
		const std::string *rd;
		Immediate imm;

		WASMSetNode(ASTNode *imm_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Set; }
		std::string debugExtra() const override;
	};

	struct WASMLiNode: public WASMBaseNode {
		const std::string *rd;
		Immediate imm;
		bool isByte;

		WASMLiNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Li; }
		std::string debugExtra() const override;
	};

	struct WASMSiNode: public WASMBaseNode {
		const std::string *rs;
		Immediate imm;
		bool isByte;

		WASMSiNode(ASTNode *rs_, ASTNode *imm_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Si; }
		std::string debugExtra() const override;
	};

	struct WASMLniNode: public WASMLiNode {
		WASMLniNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Lni; }
		std::string debugExtra() const override;
	};


	struct WASMHalfMemoryNode: public WASMBaseNode {
		const std::string *rs, *rd;

		WASMHalfMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_);
	};

	struct WASMChNode: public WASMHalfMemoryNode {
		WASMChNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Ch; }
		std::string debugExtra() const override;
	};

	struct WASMLhNode: public WASMHalfMemoryNode {
		WASMLhNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Lh; }
		std::string debugExtra() const override;
	};

	struct WASMShNode: public WASMHalfMemoryNode {
		WASMShNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Sh; }
		std::string debugExtra() const override;
	};

	struct WASMCmpNode: public WASMBaseNode {
		const std::string *rs, *rd;

		WASMCmpNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Cmp; }
		std::string debugExtra() const override;
	};

	struct WASMCmpiNode: public WASMBaseNode {
		const std::string *rs;
		Immediate imm;

		WASMCmpiNode(ASTNode *rs_, ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::Cmpi; }
		std::string debugExtra() const override;
	};

	struct WASMSelNode: public WASMBaseNode {
		enum class Oper {Equal, Less, Greater, NotEqual};

		const std::string *rs, *rt, *rd;
		Oper oper;
		WASMSelNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Sel; }
		std::string debugExtra() const override;
	};

	struct WASMJNode: public WASMBaseNode {
		Immediate addr;
		WASMCondition condition;
		bool link;

		WASMJNode(ASTNode *cond, ASTNode *colons, ASTNode *addr_);
		WASMNodeType nodeType() const override { return WASMNodeType::J; }
		std::string debugExtra() const override;
	};

	struct WASMJcNode: public WASMBaseNode {
		bool link;
		Immediate addr;
		const std::string *rs;

		WASMJcNode(WASMJNode *, ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jc; }
		std::string debugExtra() const override;
	};

	// Used for both jr and jrl.
	struct WASMJrNode: public WASMBaseNode {
		WASMCondition condition;
		bool link;
		const std::string *rd;

		WASMJrNode(ASTNode *cond, ASTNode *colons, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jr; }
		std::string debugExtra() const override;
	};

	// Used for both jrc and jrlc.
	struct WASMJrcNode: public WASMBaseNode {
		bool link;
		const std::string *rs, *rd;

		WASMJrcNode(WASMJrNode *, ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jrc; }
		std::string debugExtra() const override;
	};

	// Used for both sspush and sspop.
	struct WASMSizedStackNode: public WASMBaseNode {
		long size;
		const std::string *rs;
		bool isPush;

		WASMSizedStackNode(ASTNode *size_, ASTNode *rs_, bool is_push);
		WASMNodeType nodeType() const override { return WASMNodeType::SizedStack; }
		std::string debugExtra() const override;
	};
}