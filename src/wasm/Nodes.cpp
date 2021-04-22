#include <iostream>

#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "wasm/Nodes.h"
#include "wasm/Registers.h"

#include "compiler/Function.h"
#include "instruction/ModRInstruction.h"
#include "instruction/DivRInstruction.h"
#include "instruction/DivuRInstruction.h"
#include "instruction/ComparisonRInstruction.h"
#include "instruction/AndRInstruction.h"
#include "instruction/OrRInstruction.h"
#include "instruction/XorRInstruction.h"
#include "instruction/NandRInstruction.h"
#include "instruction/NorRInstruction.h"
#include "instruction/XnorRInstruction.h"
#include "instruction/LogicalAndRInstruction.h"
#include "instruction/LogicalOrRInstruction.h"
#include "instruction/LogicalXorRInstruction.h"
#include "instruction/LogicalNandRInstruction.h"
#include "instruction/LogicalNorRInstruction.h"
#include "instruction/LogicalXnorRInstruction.h"
#include "instruction/AddRInstruction.h"
#include "instruction/SubRInstruction.h"

static std::string cyan(const std::string &interior) {
	return "\e[36m" + interior + "\e[39m";
}

static std::string dim(const std::string &interior) {
	return "\e[2m" + interior + "\e[22m";
}

static std::string green(const std::string &interior) {
	return "\e[32m" + interior + "\e[39m";
}

static std::string red(const std::string &interior) {
	return "\e[31m" + interior + "\e[39m";
}

static std::string orange(const std::string &interior) {
	return "\e[38;5;202m" + interior + "\e[39m";
}

static std::string blue(const std::string &interior) {
	return "\e[34m" + interior + "\e[39m";
}

namespace LL2W {
	static WASMCondition getCondition(const std::string &str) {
		if (str == "0")
			return WASMCondition::Zero;
		if (str == "+")
			return WASMCondition::Positive;
		if (str == "-")
			return WASMCondition::Negative;
		if (str == "*")
			return WASMCondition::NonZero;
		if (!str.empty())
			wasmerror("Invalid condition: " + str);
		return WASMCondition::None;
	}

	static const char * conditionString(WASMCondition condition) {
		switch (condition) {
			case WASMCondition::None:     return "";
			case WASMCondition::Zero:     return "0";
			case WASMCondition::Positive: return "+";
			case WASMCondition::Negative: return "-";
			case WASMCondition::NonZero:  return "*";
			default:
				throw std::runtime_error("Invalid condition in WASMJNode: "
					+ std::to_string(static_cast<int>(condition)));
		}
	}

	static std::string stringify(const Immediate &imm, const bool colored = true) {
		if (colored) {
			if (std::holds_alternative<long>(imm))
				return green(std::to_string(std::get<long>(imm)));
			return orange(*std::get<const std::string *>(imm));
		} else if (std::holds_alternative<long>(imm))
			return std::to_string(std::get<long>(imm));
		return *std::get<const std::string *>(imm);
	}

	static Immediate getImmediate(ASTNode *node) {
		if (node->symbol == WASM_IMMEDIATE)
			return dynamic_cast<WASMImmediateNode *>(node)->imm;
		if (node->symbol == WASMTOK_NUMBER)
			return node->atoi();
		return node->lexerInfo;
	}

	WASMBaseNode::WASMBaseNode(int sym): ASTNode(wasmParser, sym) {}

	std::shared_ptr<Variable> WASMInstructionNode::convertVariable(Function &function, VarMap &map,
	const std::string *name) {
		if (name->substr(0, 2) == "$$")
			return function.makePrecoloredVariable(registerMap.at(name), nullptr);
		if (map.count(name) == 0) {
			std::shared_ptr<Variable> new_var = function.newVariable();
			map.emplace(name, new_var);
			return new_var;
		} else {
			return map.at(name);
		}
	}

	WASMImmediateNode::WASMImmediateNode(ASTNode *node): WASMBaseNode(WASM_IMMEDIATE), imm(getImmediate(node)) {
		delete node;
	}

	std::string WASMImmediateNode::debugExtra() const {
		return stringify(imm);
	}

	WASMImmediateNode::operator std::string() const {
		return stringify(imm, false);
	}

	RNode::RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_):
	WASMInstructionNode(WASM_RNODE),
	rs(rs_->lexerInfo), oper(oper_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo), operToken(oper_->symbol),
	isUnsigned(!!unsigned_) {
		delete rs_;
		delete oper_;
		if (oper_ != rt_)
			delete rt_;
		delete rd_;
		if (unsigned_)
			delete unsigned_;
	}

	std::string RNode::debugExtra() const {
		return cyan(*rs) + " " + dim(*oper) + " " + cyan(*rt) + dim(" -> ") + cyan(*rd) + (isUnsigned? " /u" : "");
	}

	RNode::operator std::string() const {
		if (*oper == "!" || *oper == "~")
			return *oper + *rs + " -> " + *rd + (isUnsigned? " /u" : "");
		return *rs + " " + *oper + " " + *rt + " -> " + *rd + (isUnsigned? " /u" : "");
	}

	std::unique_ptr<WhyInstruction> RNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };

		switch (operToken) {
			case WASMTOK_PERCENT: return std::make_unique<ModRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_SLASH:
				if (isUnsigned) return std::make_unique<DivuRInstruction>(conv(rs), conv(rt), conv(rd));
				return std::make_unique<DivRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_LANGLE:
				return std::make_unique<ComparisonRInstruction>(conv(rs), conv(rt), conv(rd),
					isUnsigned? IcmpCond::Ult : IcmpCond::Slt);
			case WASMTOK_LEQ:
				return std::make_unique<ComparisonRInstruction>(conv(rs), conv(rt), conv(rd),
					isUnsigned? IcmpCond::Ule : IcmpCond::Sle);
			case WASMTOK_DEQ:
				return std::make_unique<ComparisonRInstruction>(conv(rs), conv(rt), conv(rd), IcmpCond::Eq);
			case WASMTOK_RANGLE:
				return std::make_unique<ComparisonRInstruction>(conv(rs), conv(rt), conv(rd),
					isUnsigned? IcmpCond::Ugt : IcmpCond::Sgt);
			case WASMTOK_GEQ:
				return std::make_unique<ComparisonRInstruction>(conv(rs), conv(rt), conv(rd),
					isUnsigned? IcmpCond::Uge : IcmpCond::Sge);
			case WASMTOK_AND:
				return std::make_unique<AndRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_OR:
				return std::make_unique<OrRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_X:
				return std::make_unique<XorRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_NAND:
				return std::make_unique<NandRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_NOR:
				return std::make_unique<NorRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_XNOR:
				return std::make_unique<XnorRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_LAND:
				return std::make_unique<LogicalAndRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_LOR:
				return std::make_unique<LogicalOrRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_LXOR:
				return std::make_unique<LogicalXorRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_LNAND:
				return std::make_unique<LogicalNandRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_LNOR:
				return std::make_unique<LogicalNorRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_LXNOR:
				return std::make_unique<LogicalXnorRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_PLUS:
				return std::make_unique<AddRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_MINUS:
				return std::make_unique<SubRInstruction>(conv(rs), conv(rt), conv(rd));
			default: return nullptr;
		}
	}

	INode::INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm_, ASTNode *rd_, ASTNode *unsigned_):
	WASMInstructionNode(WASM_INODE),
	rs(rs_->lexerInfo), oper(oper_->lexerInfo), rd(rd_->lexerInfo), imm(getImmediate(imm_)), isUnsigned(!!unsigned_) {
		delete rs_;
		delete oper_;
		delete imm_;
		delete rd_;
		if (unsigned_)
			delete unsigned_;
	}

	std::string INode::debugExtra() const {
		return cyan(*rs) + " " + dim(*oper) + " " + stringify(imm) + dim(" -> ") + cyan(*rd) + (isUnsigned? " /u" : "");
	}

	INode::operator std::string() const {
		return *rs + " " + *oper + " " + stringify(imm, false) + " -> " + *rd + (isUnsigned? " /u" : "");
	}

	WASMMemoryNode::WASMMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
	WASMInstructionNode(sym), rs(rs_->lexerInfo), rd(rd_->lexerInfo), isByte(!!byte_) {
		delete rs_;
		delete rd_;
		if (byte_)
			delete byte_;
	}

	WASMCopyNode::WASMCopyNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMMemoryNode(WASM_COPYNODE, rs_, rd_, byte_) {}

	std::string WASMCopyNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> [") + cyan(*rd) + dim("]") + (isByte? " /b" : "");
	}

	WASMCopyNode::operator std::string() const {
		return "[" + *rs + "] -> [" + *rd + "]" + (isByte? " /b" : "");
	}

	WASMLoadNode::WASMLoadNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMMemoryNode(WASM_LOADNODE, rs_, rd_, byte_) {}

	std::string WASMLoadNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> ") + cyan(*rd) + (isByte? " /b" : "");
	}

	WASMLoadNode::operator std::string() const {
		return "[" + *rs + "] -> " + *rd + (isByte? " /b" : "");
	}

	WASMStoreNode::WASMStoreNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMMemoryNode(WASM_STORENODE, rs_, rd_, byte_) {}

	std::string WASMStoreNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + cyan(*rd) + dim("]") + (isByte? " /b" : "");
	}

	WASMStoreNode::operator std::string() const {
		return *rs + " -> [" + *rd + "]" + (isByte? " /b" : "");
	}

	WASMSetNode::WASMSetNode(ASTNode *imm_, ASTNode *rd_):
	WASMInstructionNode(WASM_SETNODE), rd(rd_->lexerInfo), imm(getImmediate(imm_)) {
		delete imm_;
		delete rd_;
	}

	std::string WASMSetNode::debugExtra() const {
		return stringify(imm) + dim(" -> ") + cyan(*rd);
	}

	WASMSetNode::operator std::string() const {
		return stringify(imm, false) + " -> " + *rd;
	}

	WASMLiNode::WASMLiNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_):
	WASMInstructionNode(WASM_LINODE), rd(rd_->lexerInfo), imm(getImmediate(imm_)), isByte(!!byte_) {
		delete imm_;
		delete rd_;
		if (byte_)
			delete byte_;
	}

	std::string WASMLiNode::debugExtra() const {
		return dim("[") + stringify(imm) + dim("] -> ") + cyan(*rd) + (isByte? " /b" : "");
	}

	WASMLiNode::operator std::string() const {
		return "[" + stringify(imm, false) + "] -> " + *rd + (isByte? " /b" : "");
	}

	WASMSiNode::WASMSiNode(ASTNode *rs_, ASTNode *imm_, ASTNode *byte_):
	WASMInstructionNode(WASM_SINODE), rs(rs_->lexerInfo), imm(getImmediate(imm_)), isByte(!!byte_) {
		delete rs_;
		delete imm_;
		if (byte_)
			delete byte_;
	}

	std::string WASMSiNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + stringify(imm) + dim("]") + (isByte? " /b" : "");
	}

	WASMSiNode::operator std::string() const {
		return *rs + " -> [" + stringify(imm, false) + "]" + (isByte? " /b" : "");
	}

	WASMLniNode::WASMLniNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_): WASMLiNode(imm_, rd_, byte_) {
		symbol = WASM_LNINODE;
	}

	std::string WASMLniNode::debugExtra() const {
		return dim("[") + stringify(imm) + dim("] -> [") + cyan(*rd) + dim("]") + (isByte? " /b" : "");
	}

	WASMLniNode::operator std::string() const {
		return "[" + stringify(imm, false) + "] -> [" + *rd + "]" + (isByte? " /b" : "");
	}

	WASMHalfMemoryNode::WASMHalfMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_):
	WASMInstructionNode(sym), rs(rs_->lexerInfo), rd(rd_->lexerInfo) {
		delete rs_;
		delete rd_;
	}

	WASMChNode::WASMChNode(ASTNode *rs_, ASTNode *rd_):
		WASMHalfMemoryNode(WASM_CHNODE, rs_, rd_) {}

	std::string WASMChNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> [") + cyan(*rd) + dim("]") + " /h";
	}

	WASMChNode::operator std::string() const {
		return "[" + *rs + "] -> [" + *rd + "] /h";
	}

	WASMLhNode::WASMLhNode(ASTNode *rs_, ASTNode *rd_):
		WASMHalfMemoryNode(WASM_LHNODE, rs_, rd_) {}

	std::string WASMLhNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> ") + cyan(*rd) + " /h";
	}

	WASMLhNode::operator std::string() const {
		return "[" + *rs + "] -> " + *rd + " /h";
	}

	WASMShNode::WASMShNode(ASTNode *rs_, ASTNode *rd_):
		WASMHalfMemoryNode(WASM_SHNODE, rs_, rd_) {}

	std::string WASMShNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + cyan(*rd) + dim("]") + " /h";
	}

	WASMShNode::operator std::string() const {
		return *rs + " -> [" + *rd + "] /h";
	}

	WASMCmpNode::WASMCmpNode(ASTNode *rs_, ASTNode *rd_):
	WASMInstructionNode(WASM_CMPNODE), rs(rs_->lexerInfo), rd(rd_->lexerInfo) {
		delete rs_;
		delete rd_;
	}

	std::string WASMCmpNode::debugExtra() const {
		return cyan(*rs) + dim(" ~ ") + cyan(*rd);
	}

	WASMCmpNode::operator std::string() const {
		return *rs + " ~ " + *rd;
	}

	WASMCmpiNode::WASMCmpiNode(ASTNode *rs_, ASTNode *imm_):
	WASMInstructionNode(WASM_CMPINODE), rs(rs_->lexerInfo), imm(getImmediate(imm_)) {
		delete rs_;
		delete imm_;
	}

	std::string WASMCmpiNode::debugExtra() const {
		return cyan(*rs) + dim(" ~ ") + stringify(imm);
	}

	WASMCmpiNode::operator std::string() const {
		return *rs + " ~ " + stringify(imm, false);
	}

	WASMSelNode::WASMSelNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_):
	WASMInstructionNode(WASM_SELNODE), rs(rs_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo) {
		delete rs_;
		delete rt_;
		delete rd_;
		if (*oper_->lexerInfo == "=")
			oper = Oper::Equal;
		else if (*oper_->lexerInfo == "<")
			oper = Oper::Less;
		else if (*oper_->lexerInfo == ">")
			oper = Oper::Greater;
		else if (*oper_->lexerInfo == "!=")
			oper = Oper::NotEqual;
		else
			wasmerror("Invalid operator: " + *oper_->lexerInfo);
		delete oper_;
	}

	std::string WASMSelNode::debugExtra() const {
		const char *oper_;
		switch (oper) {
			case Oper::Equal:    oper_ = "=";  break;
			case Oper::Less:     oper_ = "<";  break;
			case Oper::Greater:  oper_ = ">";  break;
			case Oper::NotEqual: oper_ = "!="; break;
			default:
				throw std::runtime_error("Invalid operator in WASMSelNode: " + std::to_string(static_cast<int>(oper)));
		}
		return dim("[") + cyan(*rs) + " " + dim(oper_) + " " + cyan(*rt) + dim("] -> ") + cyan(*rd);
	}

	WASMSelNode::operator std::string() const {
		const char *oper_;
		switch (oper) {
			case Oper::Equal:    oper_ = "=";  break;
			case Oper::Less:     oper_ = "<";  break;
			case Oper::Greater:  oper_ = ">";  break;
			case Oper::NotEqual: oper_ = "!="; break;
			default:
				throw std::runtime_error("Invalid operator in WASMSelNode: " + std::to_string(static_cast<int>(oper)));
		}
		return "[" + *rs + " " + oper_ + " " + *rt + "] -> " + *rd;
	}

	WASMJNode::WASMJNode(ASTNode *cond, ASTNode *colons, ASTNode *addr_):
	WASMInstructionNode(WASM_JNODE), addr(getImmediate(addr_)), link(!colons->empty()) {
		delete addr_;
		delete colons;
		if (!cond) {
			condition = WASMCondition::None;
		} else {
			condition = getCondition(*cond->lexerInfo);
			delete cond;
		}
	}

	std::string WASMJNode::debugExtra() const {
		return dim(conditionString(condition) + std::string(link? "::" : ":")) + " " + stringify(addr);
	}

	WASMJNode::operator std::string() const {
		return conditionString(condition) + std::string(link? "::" : ":") + " " + stringify(addr, false);
	}

	WASMJcNode::WASMJcNode(WASMJNode *j, ASTNode *rs_):
	WASMInstructionNode(WASM_JCNODE), link(j? j->link : false), addr(j? j->addr : 0), rs(rs_->lexerInfo) {
		if (!j) {
			wasmerror("No WASMCJNode found in jc instruction");
		} else {
			if (j->condition != WASMCondition::None)
				wasmerror("Conditions specified for jc instruction will be ignored");
			delete j;
		}
		delete rs_;
	}

	std::string WASMJcNode::debugExtra() const {
		return dim(link? "::" : ":") + " " + stringify(addr) + red(" if ") + cyan(*rs);
	}

	WASMJcNode::operator std::string() const {
		return std::string(link? "::" : ":") + " " + stringify(addr, false) + " if " + *rs;
	}

	WASMJrNode::WASMJrNode(ASTNode *cond, ASTNode *colons, ASTNode *rd_):
	WASMInstructionNode(WASM_JRNODE), link(!colons->empty()), rd(rd_->lexerInfo) {
		delete colons;
		delete rd_;
		if (!cond) {
			condition = WASMCondition::None;
		} else {
			condition = getCondition(*cond->lexerInfo);
			delete cond;
		}
	}

	std::string WASMJrNode::debugExtra() const {
		return dim(conditionString(condition) + std::string(link? "::" : ":")) + " " + cyan(*rd);
	}

	WASMJrNode::operator std::string() const {
		return conditionString(condition) + std::string(link? "::" : ":") + " " + *rd;
	}

	WASMJrcNode::WASMJrcNode(WASMJrNode *jr, ASTNode *rs_):
	WASMInstructionNode(WASM_JRCNODE), link(jr? jr->link : false), rs(rs_->lexerInfo), rd(jr? jr->rd : nullptr) {
		if (!jr) {
			wasmerror("No WASMCJrNode found in jr(l)c instruction");
		} else {
			if (jr->condition != WASMCondition::None)
				wasmerror("Conditions specified for jr(l)c instruction will be ignored");
			delete jr;
		}
		delete rs_;
	}

	std::string WASMJrcNode::debugExtra() const {
		return dim(link? "::" : ":") + " " + cyan(*rd) + red(" if ") + cyan(*rs);
	}

	WASMJrcNode::operator std::string() const {
		return std::string(link? "::" : ":") + " " + *rd + " if " + *rs;
	}

	WASMSizedStackNode::WASMSizedStackNode(ASTNode *size_, ASTNode *rs_, bool is_push):
	WASMInstructionNode(WASM_SSNODE), size(size_->atoi()), rs(rs_->lexerInfo), isPush(is_push) {
		delete size_;
		delete rs_;
	}

	std::string WASMSizedStackNode::debugExtra() const {
		return dim(std::string(isPush? "[" : "]") + ":" + std::to_string(size)) + " " + cyan(*rs);
	}

	WASMSizedStackNode::operator std::string() const {
		return std::string(isPush? "[" : "]") + ":" + std::to_string(size) + " " + *rs;
	}

	WASMMultRNode::WASMMultRNode(ASTNode *rs_, ASTNode *rt_, ASTNode *unsigned_):
	WASMInstructionNode(WASM_MULTRNODE), rs(rs_->lexerInfo), rt(rt_->lexerInfo), isUnsigned(!!unsigned_) {
		delete rs_;
		delete rt_;
		if (unsigned_)
			delete unsigned_;
	}

	std::string WASMMultRNode::debugExtra() const {
		return cyan(*rs) + dim(" * ") + cyan(*rt) + (isUnsigned? " /u" : "");
	}

	WASMMultRNode::operator std::string() const {
		return *rs + " * " + *rt + (isUnsigned? " /u" : "");
	}

	WASMMultINode::WASMMultINode(ASTNode *rs_, ASTNode *imm_, ASTNode *unsigned_):
	WASMInstructionNode(WASM_MULTINODE), rs(rs_->lexerInfo), imm(getImmediate(imm_)), isUnsigned(!!unsigned_) {
		delete rs_;
		delete imm_;
		if (unsigned_)
			delete unsigned_;
	}

	std::string WASMMultINode::debugExtra() const {
		return cyan(*rs) + dim(" * ") + stringify(imm) + (isUnsigned? " /u" : "");
	};

	WASMMultINode::operator std::string() const {
		return *rs + " * " + stringify(imm, false) + (isUnsigned? " /u" : "");
	}

	WASMDiviINode::WASMDiviINode(ASTNode *imm_, ASTNode *rs_, ASTNode *rd_, ASTNode *unsigned_):
	WASMInstructionNode(WASM_DIVIINODE), rs(rs_->lexerInfo), rd(rd_->lexerInfo), imm(getImmediate(imm_)),
	isUnsigned(!!unsigned_) {
		delete rs_;
		delete rd_;
		delete imm_;
		if (unsigned_)
			delete unsigned_;
	}

	std::string WASMDiviINode::debugExtra() const {
		return stringify(imm) + dim(" / ") + cyan(*rs) + dim(" -> ") + cyan(*rd) + (isUnsigned? " /u" : "");
	}

	WASMDiviINode::operator std::string() const {
		return stringify(imm, false) + " / " + *rs + " -> " + *rd + (isUnsigned? " /u" : "");
	}

	WASMLuiNode::WASMLuiNode(ASTNode *imm_, ASTNode *rd_):
	WASMInstructionNode(WASM_LUINODE), rd(rd_->lexerInfo), imm(getImmediate(imm_)) {
		delete imm_;
		delete rd_;
	}

	std::string WASMLuiNode::debugExtra() const {
		return "lui" + dim(": ") + stringify(imm) + dim(" -> ") + cyan(*rd);
	}

	WASMLuiNode::operator std::string() const {
		return "lui: " + stringify(imm, false) + " -> " + *rd;
	}

	WASMStackNode::WASMStackNode(ASTNode *rd_, bool is_push):
	WASMInstructionNode(WASM_STACKNODE), rd(rd_->lexerInfo), isPush(is_push) {
		delete rd_;
	}

	std::string WASMStackNode::debugExtra() const {
		return dim(isPush? "[" : "]") + " " + cyan(*rd);
	}

	WASMStackNode::operator std::string() const {
		return std::string(isPush? "[" : "]") + " " + *rd;
	}

	WASMNopNode::WASMNopNode(): WASMInstructionNode(WASM_NOPNODE) {}

	std::string WASMNopNode::debugExtra() const {
		return dim("<>");
	}

	WASMNopNode::operator std::string() const {
		return "<>";
	}

	WASMIntINode::WASMIntINode(ASTNode *imm_): WASMInstructionNode(WASM_INTINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMIntINode::debugExtra() const {
		return blue("int") + " " + stringify(imm);
	}

	WASMIntINode::operator std::string() const {
		return "int " + stringify(imm, false);
	}

	WASMRitINode::WASMRitINode(ASTNode *imm_): WASMInstructionNode(WASM_RITINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMRitINode::debugExtra() const {
		return blue("rit") + " " + stringify(imm);
	}

	WASMRitINode::operator std::string() const {
		return "rit " + stringify(imm, false);
	}

	WASMTimeINode::WASMTimeINode(ASTNode *imm_): WASMInstructionNode(WASM_TIMEINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMTimeINode::debugExtra() const {
		return blue("time") + " " + stringify(imm);
	}

	WASMTimeINode::operator std::string() const {
		return "time " + stringify(imm, false);
	}

	WASMTimeRNode::WASMTimeRNode(ASTNode *rs_): WASMInstructionNode(WASM_TIMERNODE), rs(rs_->lexerInfo) {
		delete rs_;
	}

	std::string WASMTimeRNode::debugExtra() const {
		return blue("time") + " " + cyan(*rs);
	}

	WASMTimeRNode::operator std::string() const {
		return "time " + *rs;
	}

	WASMRingINode::WASMRingINode(ASTNode *imm_): WASMInstructionNode(WASM_RINGINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMRingINode::debugExtra() const {
		return blue("ring") + " " + stringify(imm);
	}

	WASMRingINode::operator std::string() const {
		return "ring " + stringify(imm, false);
	}

	WASMRingRNode::WASMRingRNode(ASTNode *rs_): WASMInstructionNode(WASM_RINGRNODE), rs(rs_->lexerInfo) {
		delete rs_;
	}

	std::string WASMRingRNode::debugExtra() const {
		return blue("ring") + " " + cyan(*rs);
	}

	WASMRingRNode::operator std::string() const {
		return "ring " + *rs;
	}

	WASMPrintNode::WASMPrintNode(ASTNode *rs_, ASTNode *type_):
	WASMInstructionNode(WASM_PRINTNODE), rs(rs_->lexerInfo) {
		delete rs_;
		const std::string &typestr = *type_->lexerInfo;
		if (typestr == "prx")
			type = WASMPrintType::Hex;
		else if (typestr == "prd")
			type = WASMPrintType::Dec;
		else if (typestr == "prc")
			type = WASMPrintType::Char;
		else if (typestr == "print")
			type = WASMPrintType::Full;
		else if (typestr == "prb")
			type = WASMPrintType::Bin;
		else {
			wasmerror("Invalid print type: " + typestr);
			type = WASMPrintType::Full;
		}
		delete type_;
	}

	std::string WASMPrintNode::debugExtra() const {
		switch (type) {
			case WASMPrintType::Hex:  return "<" + blue("prx")   + " " + cyan(*rs) + ">";
			case WASMPrintType::Dec:  return "<" + blue("prd")   + " " + cyan(*rs) + ">";
			case WASMPrintType::Char: return "<" + blue("prc")   + " " + cyan(*rs) + ">";
			case WASMPrintType::Full: return "<" + blue("print") + " " + cyan(*rs) + ">";
			case WASMPrintType::Bin:  return "<" + blue("prb")   + " " + cyan(*rs) + ">";
			default:
				return red("???");
		}
	}

	WASMPrintNode::operator std::string() const {
		switch (type) {
			case WASMPrintType::Hex:  return "<prx "   + *rs + ">";
			case WASMPrintType::Dec:  return "<prd "   + *rs + ">";
			case WASMPrintType::Char: return "<prc "   + *rs + ">";
			case WASMPrintType::Full: return "<print " + *rs + ">";
			case WASMPrintType::Bin:  return "<prb "   + *rs + ">";
			default:
				return "???";
		}
	}

	WASMHaltNode::WASMHaltNode(): WASMInstructionNode(WASM_HALTNODE) {}

	std::string WASMHaltNode::debugExtra() const {
		return "<" + blue("halt") + ">";
	}

	WASMHaltNode::operator std::string() const {
		return "<halt>";
	}

	WASMSleepRNode::WASMSleepRNode(ASTNode *rs_): WASMInstructionNode(WASM_SLEEPRNODE), rs(rs_->lexerInfo) {
		delete rs_;
	}

	std::string WASMSleepRNode::debugExtra() const {
		return "<" + blue("sleep") + " " + cyan(*rs) + ">";
	}

	WASMSleepRNode::operator std::string() const {
		return "<sleep " + *rs + ">";
	}

	WASMPageNode::WASMPageNode(bool on_): WASMInstructionNode(WASM_PAGENODE), on(on_) {}

	std::string WASMPageNode::debugExtra() const {
		return blue("page") + " " + (on? "on" : "off");
	}

	WASMPageNode::operator std::string() const {
		return "page " + std::string(on? "on" : "off");
	}

	WASMSetptINode::WASMSetptINode(ASTNode *imm_): WASMInstructionNode(WASM_SETPTINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMSetptINode::debugExtra() const {
		return blue("setpt") + " " + stringify(imm);
	}

	WASMSetptINode::operator std::string() const {
		return "setpt " + stringify(imm, false);
	}

	WASMMvNode::WASMMvNode(ASTNode *rs_, ASTNode *rd_):
	WASMInstructionNode(WASM_MVNODE), rs(rs_->lexerInfo), rd(rd_->lexerInfo) {
		delete rs_;
		delete rd_;
	}

	std::string WASMMvNode::debugExtra() const {
		return cyan(*rs) + dim(" -> ") + cyan(*rd);
	}

	WASMMvNode::operator std::string() const {
		return *rs + " -> " + *rd;
	}
}
