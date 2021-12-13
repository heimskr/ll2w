#pragma once

#include <memory>
#include <unordered_map>

#include "compiler/Immediate.h"
#include "parser/ASTNode.h"
#include "parser/Enums.h"
#include "instruction/WhyInstruction.h"

namespace LL2W {
	enum class WASMNodeType {
		Immediate, RType, IType, Copy, Load, Store, Set, Li, Si, Lni, Ch, Lh, Sh, Cmp, Cmpi, Sel, J, Jc, Jr, Jrc, Mv,
		SizedStack, MultR, MultI, DiviI, Lui, Stack, Nop, IntI, RitI, TimeI, TimeR, RingI, RingR, Print, Halt, SleepR,
		Page, SetptI, Label, SetptR, Svpg, Query, PseudoPrint, Rest, IO, Interrupts, InverseShift, Sext, PageStack,
		TranslateAddress,
	};

	class WhyInstruction;
	class Function;
	class Variable;

	using VarMap = std::unordered_map<const std::string *, std::shared_ptr<Variable>>;

	struct WASMBaseNode: ASTNode {
		WASMBaseNode(int sym);
		virtual WASMNodeType nodeType() const = 0;
		virtual operator std::string() const = 0;
	};

	struct WASMInstructionNode: WASMBaseNode {
		using WASMBaseNode::WASMBaseNode;

		std::shared_ptr<Variable> convertVariable(Function &, VarMap &, const std::string *);
		virtual std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) { return nullptr; }
	};

	struct WASMImmediateNode: WASMBaseNode {
		Immediate imm;

		WASMImmediateNode(ASTNode *);
		virtual WASMNodeType nodeType() const override { return WASMNodeType::Immediate; }
		std::string debugExtra() const override;
		operator std::string() const override;
	};

	struct WASMLabelNode: WASMInstructionNode { // Not technically an instruction, but still.
		const std::string *label;

		WASMLabelNode(ASTNode *);
		virtual WASMNodeType nodeType() const override { return WASMNodeType::Label; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct RNode: WASMInstructionNode {
		const std::string *rs, *oper, *rt, *rd;
		int operToken;
		bool isUnsigned;
		
		RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_);
		WASMNodeType nodeType() const override { return WASMNodeType::RType; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct INode: WASMInstructionNode {
		const std::string *rs, *oper, *rd;
		int operToken;
		Immediate imm;
		bool isUnsigned;

		INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm, ASTNode *rd_, ASTNode *unsigned_);
		WASMNodeType nodeType() const override { return WASMNodeType::IType; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMMemoryNode: WASMInstructionNode {
		const std::string *rs, *rd;
		bool isByte;

		WASMMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
	};

	struct WASMCopyNode: WASMMemoryNode {
		WASMCopyNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Copy; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMLoadNode: WASMMemoryNode {
		WASMLoadNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Load; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMStoreNode: WASMMemoryNode {
		WASMStoreNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Store; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMSetNode: WASMInstructionNode {
		const std::string *rd;
		Immediate imm;

		WASMSetNode(ASTNode *imm_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Set; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMLiNode: WASMInstructionNode {
		const std::string *rd;
		Immediate imm;
		bool isByte;

		WASMLiNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Li; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMSiNode: WASMInstructionNode {
		const std::string *rs;
		Immediate imm;
		bool isByte;

		WASMSiNode(ASTNode *rs_, ASTNode *imm_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Si; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMLniNode: WASMLiNode {
		WASMLniNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_);
		WASMNodeType nodeType() const override { return WASMNodeType::Lni; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMHalfMemoryNode: WASMInstructionNode {
		const std::string *rs, *rd;

		WASMHalfMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_);
	};

	struct WASMChNode: WASMHalfMemoryNode {
		WASMChNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Ch; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMLhNode: WASMHalfMemoryNode {
		WASMLhNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Lh; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMShNode: WASMHalfMemoryNode {
		WASMShNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Sh; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMCmpNode: WASMInstructionNode {
		const std::string *rs, *rt;

		WASMCmpNode(ASTNode *rs_, ASTNode *rt_);
		WASMNodeType nodeType() const override { return WASMNodeType::Cmp; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMCmpiNode: WASMInstructionNode {
		const std::string *rs;
		Immediate imm;

		WASMCmpiNode(ASTNode *rs_, ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::Cmpi; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMSelNode: WASMInstructionNode {
		const std::string *rs, *rt, *rd;
		Condition condition;

		WASMSelNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Sel; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMJNode: WASMInstructionNode {
		Immediate addr;
		Condition condition;
		bool link;

		WASMJNode(ASTNode *cond, ASTNode *colons, ASTNode *addr_);
		WASMNodeType nodeType() const override { return WASMNodeType::J; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMJcNode: WASMInstructionNode {
		bool link;
		Immediate addr;
		const std::string *rs;

		WASMJcNode(WASMJNode *, ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jc; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	// Used for both jr and jrl.
	struct WASMJrNode: WASMInstructionNode {
		Condition condition;
		bool link;
		const std::string *rd;

		WASMJrNode(ASTNode *cond, ASTNode *colons, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jr; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	// Used for both jrc and jrlc.
	struct WASMJrcNode: WASMInstructionNode {
		bool link;
		const std::string *rs, *rd;

		WASMJrcNode(WASMJrNode *, ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::Jrc; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	// Used for both sspush and sspop.
	struct WASMSizedStackNode: WASMInstructionNode {
		long size;
		const std::string *rs;
		bool isPush;

		WASMSizedStackNode(ASTNode *size_, ASTNode *rs_, bool is_push);
		WASMNodeType nodeType() const override { return WASMNodeType::SizedStack; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMMultRNode: WASMInstructionNode {
		const std::string *rs, *rt;
		bool isUnsigned;

		WASMMultRNode(ASTNode *rs_, ASTNode *rt_, ASTNode *unsigned_ = nullptr);
		WASMNodeType nodeType() const override { return WASMNodeType::MultR; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMMultINode: WASMInstructionNode {
		const std::string *rs;
		Immediate imm;
		bool isUnsigned;

		WASMMultINode(ASTNode *rs_, ASTNode *imm_, ASTNode *unsigned_ = nullptr);
		WASMNodeType nodeType() const override { return WASMNodeType::MultI; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMDiviINode: WASMInstructionNode {
		const std::string *rs, *rd;
		Immediate imm;
		bool isUnsigned;

		WASMDiviINode(ASTNode *imm_, ASTNode *rs_, ASTNode *rd_, ASTNode *unsigned_ = nullptr);
		WASMNodeType nodeType() const override { return WASMNodeType::DiviI; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMLuiNode: WASMInstructionNode {
		const std::string *rd;
		Immediate imm;

		WASMLuiNode(ASTNode *imm_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Lui; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMStackNode: WASMInstructionNode {
		const std::string *reg;
		bool isPush;

		WASMStackNode(ASTNode *reg_, bool is_push);
		WASMNodeType nodeType() const override { return WASMNodeType::Stack; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMNopNode: WASMInstructionNode {
		WASMNopNode();
		WASMNodeType nodeType() const override { return WASMNodeType::Nop; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMIntINode: WASMInstructionNode {
		Immediate imm;

		WASMIntINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::IntI; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMRitINode: WASMInstructionNode {
		Immediate imm;

		WASMRitINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::RitI; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMTimeINode: WASMInstructionNode {
		Immediate imm;

		WASMTimeINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::TimeI; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMTimeRNode: WASMInstructionNode {
		const std::string *rs;

		WASMTimeRNode(ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::TimeR; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMRingINode: WASMInstructionNode {
		Immediate imm;

		WASMRingINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::RingI; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMRingRNode: WASMInstructionNode {
		const std::string *rs;

		WASMRingRNode(ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::RingR; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMPrintNode: WASMInstructionNode {
		const std::string *rs;
		PrintType type;

		WASMPrintNode(ASTNode *rs_, ASTNode *type_);
		WASMNodeType nodeType() const override { return WASMNodeType::Print; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMHaltNode: WASMInstructionNode {
		WASMHaltNode();
		WASMNodeType nodeType() const override { return WASMNodeType::Halt; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMSleepRNode: WASMInstructionNode {
		const std::string *rs;

		WASMSleepRNode(ASTNode *rs_);
		WASMNodeType nodeType() const override { return WASMNodeType::SleepR; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMPageNode: WASMInstructionNode {
		bool on;

		WASMPageNode(bool on_);
		WASMNodeType nodeType() const override { return WASMNodeType::Page; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMSetptINode: WASMInstructionNode {
		Immediate imm;

		WASMSetptINode(ASTNode *imm_);
		WASMNodeType nodeType() const override { return WASMNodeType::SetptI; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMSetptRNode: WASMInstructionNode {
		const std::string *rs, *rt;

		WASMSetptRNode(ASTNode *rs_, ASTNode *rt_ = nullptr);
		WASMSetptRNode(const std::string *rs_, const std::string *rt_ = nullptr);
		WASMNodeType nodeType() const override { return WASMNodeType::SetptR; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMMvNode: WASMInstructionNode {
		const std::string *rs, *rd;

		WASMMvNode(ASTNode *rs_, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Mv; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMSvpgNode: WASMInstructionNode {
		const std::string *rd;

		WASMSvpgNode(ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Svpg; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMQueryNode: WASMInstructionNode {
		QueryType type;
		const std::string *rd;

		WASMQueryNode(QueryType, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::Query; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMPseudoPrintNode: WASMInstructionNode {
		Immediate imm;
		const std::string *text = nullptr;

		WASMPseudoPrintNode(ASTNode *imm_);
		WASMPseudoPrintNode(const std::string *text_);
		WASMNodeType nodeType() const override { return WASMNodeType::PseudoPrint; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMRestNode: WASMInstructionNode {
		WASMRestNode();
		WASMNodeType nodeType() const override { return WASMNodeType::Rest; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMIONode: WASMInstructionNode {
		const std::string *ident = nullptr;

		WASMIONode(const std::string *ident_);
		WASMNodeType nodeType() const override { return WASMNodeType::IO; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMInterruptsNode: WASMInstructionNode {
		const bool enable;

		WASMInterruptsNode(bool enable_);
		WASMNodeType nodeType() const override { return WASMNodeType::Interrupts; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMInverseShiftNode: WASMInstructionNode {
		const std::string *rs, *oper, *rd;
		int operToken;
		Immediate imm;

		WASMInverseShiftNode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm, ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::InverseShift; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMSextNode: WASMInstructionNode {
		const std::string *rs, *rd;
		int size;

		WASMSextNode(ASTNode *rs_, ASTNode *rd_, ASTNode *size_);
		WASMNodeType nodeType() const override { return WASMNodeType::Sext; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMTransNode: WASMInstructionNode {
		const std::string *rs, *rd;

		WASMTransNode(const ASTNode *rs_, const ASTNode *rd_);
		WASMNodeType nodeType() const override { return WASMNodeType::TranslateAddress; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};

	struct WASMPageStackNode: WASMInstructionNode {
		bool isPush;
		const std::string *rs;
		WASMPageStackNode(bool is_push, const std::string *rs_ = nullptr);
		WASMNodeType nodeType() const override { return WASMNodeType::PageStack; }
		std::string debugExtra() const override;
		operator std::string() const override;
		std::unique_ptr<WhyInstruction> convert(Function &, VarMap &) override;
	};
}
