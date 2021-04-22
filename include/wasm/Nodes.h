#pragma once

#include <memory>
#include <unordered_map>

#include "compiler/Immediate.h"
#include "parser/ASTNode.h"

namespace LL2W {
	enum class WASMNodeType {
		Immediate, RType, IType, Copy, Load, Store, Set, Li, Si, Lni, Ch, Lh, Sh, Cmp, Cmpi, Sel, J, Jc, Jr, Jrc, Mv,
		SizedStack, MultR, MultI, DiviI, Lui, Stack, Nop, IntI, RitI, TimeI, TimeR, RingI, RingR, Print, Halt, SleepR,
		Page, SetptI
	};

	enum class WASMCondition {None, Positive, Negative, Zero, NonZero};

	enum class WASMPrintType {Hex, Dec, Char, Full, Bin};

	class WhyInstruction;
	class Function;
	class Variable;

	using VarMap = std::unordered_map<const std::string *, std::shared_ptr<Variable>>;

	struct WASMBaseNode: public ASTNode {
		WASMBaseNode(int sym);
		virtual WASMNodeType nodeType() const = 0;
		virtual operator std::string() const = 0;
	};

	struct WASMInstructionNode: public WASMBaseNode {
		using WASMBaseNode::WASMBaseNode;

		std::shared_ptr<Variable> convertVariable(Function &, VarMap &, const std::string *);
		virtual std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) { return nullptr; }
	};

	struct WASMImmediateNode: public WASMBaseNode {
		Immediate imm;

		WASMImmediateNode(ASTNode *);
		virtual WASMNodeType nodeType() const override { return WASMNodeType::Immediate; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct RNode: public WASMInstructionNode {
		const std::string *rs, *oper, *rt, *rd;
		int operToken;
		bool isUnsigned;
		
		RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_);
		WASMNodeType nodeType() const override { return WASMNodeType::RType; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct INode: public WASMInstructionNode {
		const std::string *rs, *oper, *rd;
		Immediate imm;
		bool isUnsigned;

		INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm, ASTNode *rd_, ASTNode *unsigned_);
		WASMNodeType nodeType() const override { return WASMNodeType::IType; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMMemoryNode: public WASMInstructionNode {
		const std::string *rs, *rd;
		bool isByte;

		WASMMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
	};

	struct WASMCopyNode: public WASMMemoryNode {
		WASMCopyNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Copy; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMLoadNode: public WASMMemoryNode {
		WASMLoadNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Load; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMStoreNode: public WASMMemoryNode {
		WASMStoreNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Store; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMSetNode: public WASMInstructionNode {
		const std::string *rd;
		Immediate imm;

		WASMSetNode(ASTNode *imm_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Set; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMLiNode: public WASMInstructionNode {
		const std::string *rd;
		Immediate imm;
		bool isByte;

		WASMLiNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Li; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMSiNode: public WASMInstructionNode {
		const std::string *rs;
		Immediate imm;
		bool isByte;

		WASMSiNode(ASTNode *rs_, ASTNode *imm_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Si; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMLniNode: public WASMLiNode {
		WASMLniNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Lni; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};


	struct WASMHalfMemoryNode: public WASMInstructionNode {
		const std::string *rs, *rd;

		WASMHalfMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_);
	};

	struct WASMChNode: public WASMHalfMemoryNode {
		WASMChNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Ch; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMLhNode: public WASMHalfMemoryNode {
		WASMLhNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Lh; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMShNode: public WASMHalfMemoryNode {
		WASMShNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Sh; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMCmpNode: public WASMInstructionNode {
		const std::string *rs, *rd;

		WASMCmpNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Cmp; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMCmpiNode: public WASMInstructionNode {
		const std::string *rs;
		Immediate imm;

		WASMCmpiNode(ASTNode *rs_, ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::Cmpi; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMSelNode: public WASMInstructionNode {
		enum class Oper {Equal, Less, Greater, NotEqual};

		const std::string *rs, *rt, *rd;
		Oper oper;
		WASMSelNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Sel; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMJNode: public WASMInstructionNode {
		Immediate addr;
		WASMCondition condition;
		bool link;

		WASMJNode(ASTNode *cond, ASTNode *colons, ASTNode *addr_);
		WASMNodeType nodeType() const override { return WASMNodeType::J; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMJcNode: public WASMInstructionNode {
		bool link;
		Immediate addr;
		const std::string *rs;

		WASMJcNode(WASMJNode *, ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jc; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	// Used for both jr and jrl.
	struct WASMJrNode: public WASMInstructionNode {
		WASMCondition condition;
		bool link;
		const std::string *rd;

		WASMJrNode(ASTNode *cond, ASTNode *colons, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jr; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	// Used for both jrc and jrlc.
	struct WASMJrcNode: public WASMInstructionNode {
		bool link;
		const std::string *rs, *rd;

		WASMJrcNode(WASMJrNode *, ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jrc; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	// Used for both sspush and sspop.
	struct WASMSizedStackNode: public WASMInstructionNode {
		long size;
		const std::string *rs;
		bool isPush;

		WASMSizedStackNode(ASTNode *size_, ASTNode *rs_, bool is_push);
		WASMNodeType nodeType() const override { return WASMNodeType::SizedStack; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMMultRNode: public WASMInstructionNode {
		const std::string *rs, *rt;
		bool isUnsigned;

		WASMMultRNode(ASTNode *rs_, ASTNode *rt_, ASTNode *unsigned_ = nullptr);
		WASMNodeType nodeType() const override { return WASMNodeType::MultR; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMMultINode: public WASMInstructionNode {
		const std::string *rs;
		Immediate imm;
		bool isUnsigned;

		WASMMultINode(ASTNode *rs_, ASTNode *imm_, ASTNode *unsigned_ = nullptr);
		WASMNodeType nodeType() const override { return WASMNodeType::MultI; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMDiviINode: public WASMInstructionNode {
		const std::string *rs, *rd;
		Immediate imm;
		bool isUnsigned;

		WASMDiviINode(ASTNode *imm_, ASTNode *rs_, ASTNode *rd_, ASTNode *unsigned_ = nullptr);
		WASMNodeType nodeType() const override { return WASMNodeType::DiviI; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMLuiNode: public WASMInstructionNode {
		const std::string *rd;
		Immediate imm;

		WASMLuiNode(ASTNode *imm_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Lui; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMStackNode: public WASMInstructionNode {
		const std::string *rd;
		bool isPush;

		WASMStackNode(ASTNode *rd_, bool is_push);
		WASMNodeType nodeType() const override { return WASMNodeType::Stack; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMNopNode: public WASMInstructionNode {
		WASMNopNode();
		WASMNodeType nodeType() const override { return WASMNodeType::Nop; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMIntINode: public WASMInstructionNode {
		Immediate imm;

		WASMIntINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::IntI; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMRitINode: public WASMInstructionNode {
		Immediate imm;

		WASMRitINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::RitI; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMTimeINode: public WASMInstructionNode {
		Immediate imm;

		WASMTimeINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::TimeI; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMTimeRNode: public WASMInstructionNode {
		const std::string *rs;

		WASMTimeRNode(ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::TimeR; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMRingINode: public WASMInstructionNode {
		Immediate imm;

		WASMRingINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::RingI; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMRingRNode: public WASMInstructionNode {
		const std::string *rs;

		WASMRingRNode(ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::RingR; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMPrintNode: public WASMInstructionNode {
		const std::string *rs;
		WASMPrintType type;

		WASMPrintNode(ASTNode *rs_, ASTNode *type_);
		WASMNodeType nodeType() const override { return WASMNodeType::Print; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMHaltNode: public WASMInstructionNode {
		WASMHaltNode();
		WASMNodeType nodeType() const override { return WASMNodeType::Halt; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMSleepRNode: public WASMInstructionNode {
		const std::string *rs;

		WASMSleepRNode(ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::SleepR; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMPageNode: public WASMInstructionNode {
		bool on;

		WASMPageNode(bool on_);
		WASMNodeType nodeType() const override { return WASMNodeType::Page; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMSetptINode: public WASMInstructionNode {
		Immediate imm;

		WASMSetptINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::SetptI; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMMvNode: public WASMInstructionNode {
		const std::string *rs, *rd;

		WASMMvNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Mv; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};
}
