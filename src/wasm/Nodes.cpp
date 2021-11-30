#include <iostream>

#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "wasm/Nodes.h"
#include "wasm/Registers.h"

#include "compiler/Function.h"
#include "instruction/ModRInstruction.h"
#include "instruction/ModuRInstruction.h"
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
#include "instruction/ModIInstruction.h"
#include "instruction/ModuIInstruction.h"
#include "instruction/DivuIInstruction.h"
#include "instruction/DivIInstruction.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/AndIInstruction.h"
#include "instruction/OrIInstruction.h"
#include "instruction/XorIInstruction.h"
#include "instruction/NandIInstruction.h"
#include "instruction/NorIInstruction.h"
#include "instruction/XnorIInstruction.h"
#include "instruction/LogicalAndIInstruction.h"
#include "instruction/LogicalOrIInstruction.h"
#include "instruction/LogicalXorIInstruction.h"
#include "instruction/LogicalNandIInstruction.h"
#include "instruction/LogicalNorIInstruction.h"
#include "instruction/LogicalXnorIInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/SubIInstruction.h"
#include "instruction/CopyRInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/LoadIInstruction.h"
#include "instruction/StoreIInstruction.h"
#include "instruction/LoadIndirectIInstruction.h"
#include "instruction/CompareRInstruction.h"
#include "instruction/CompareIInstruction.h"
#include "instruction/SelectInstruction.h"
#include "instruction/JumpInstruction.h"
#include "instruction/JumpConditionalInstruction.h"
#include "instruction/JumpRegisterInstruction.h"
#include "instruction/JumpRegisterConditionalInstruction.h"
#include "instruction/SizedStackPushInstruction.h"
#include "instruction/SizedStackPopInstruction.h"
#include "instruction/MultRInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/DiviIInstruction.h"
#include "instruction/LuiInstruction.h"
#include "instruction/StackPushInstruction.h"
#include "instruction/StackPopInstruction.h"
#include "instruction/Nop.h"
#include "instruction/IntIInstruction.h"
#include "instruction/RitIInstruction.h"
#include "instruction/TimeIInstruction.h"
#include "instruction/TimeRInstruction.h"
#include "instruction/RingIInstruction.h"
#include "instruction/RingRInstruction.h"
#include "instruction/PrintRInstruction.h"
#include "instruction/HaltInstruction.h"
#include "instruction/SleepRInstruction.h"
#include "instruction/PageInstruction.h"
#include "instruction/SetptIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/Label.h"
#include "instruction/SetptRInstruction.h"
#include "instruction/SvpgInstruction.h"
#include "instruction/QueryInstruction.h"
#include "instruction/NotRInstruction.h"
#include "instruction/PrintPseudoinstruction.h"
#include "instruction/MemsetInstruction.h"
#include "instruction/RestInstruction.h"
#include "instruction/IOInstruction.h"
#include "instruction/InterruptsInstruction.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"
#include "instruction/ShiftLeftLogicalInverseIInstruction.h"
#include "instruction/ShiftLeftLogicalRInstruction.h"
#include "instruction/ShiftRightArithmeticIInstruction.h"
#include "instruction/ShiftRightArithmeticInverseIInstruction.h"
#include "instruction/ShiftRightArithmeticRInstruction.h"
#include "instruction/ShiftRightLogicalIInstruction.h"
#include "instruction/ShiftRightLogicalInverseIInstruction.h"
#include "instruction/ShiftRightLogicalRInstruction.h"
#include "instruction/Sext32RInstruction.h"
#include "instruction/Sext16RInstruction.h"
#include "instruction/Sext8RInstruction.h"

static std::string cyan(const std::string &interior) {
	return "\e[36m" + interior + "\e[39m";
}

static std::string dim(const std::string &interior) {
	return "\e[2m" + interior + "\e[22m";
}

static std::string red(const std::string &interior) {
	return "\e[31m" + interior + "\e[39m";
}

static std::string blue(const std::string &interior) {
	return "\e[34m" + interior + "\e[39m";
}

static std::string bold(const std::string &interior) {
	return "\e[1m" + interior + "\e[22m";
}

namespace LL2W {
	static Condition getCondition(const std::string &str) {
		if (str == "0")
			return Condition::Zero;
		if (str == "+")
			return Condition::Positive;
		if (str == "-")
			return Condition::Negative;
		if (str == "*")
			return Condition::Nonzero;
		if (!str.empty())
			wasmerror("Invalid condition: " + str);
		return Condition::None;
	}

	static const char * conditionString(Condition condition) {
		switch (condition) {
			case Condition::None:     return "";
			case Condition::Zero:     return "0";
			case Condition::Positive: return "+";
			case Condition::Negative: return "-";
			case Condition::Nonzero:  return "*";
			default:
				throw std::runtime_error("Invalid condition in WASMJNode: "
					+ std::to_string(static_cast<int>(condition)));
		}
	}

	static Immediate getImmediate(ASTNode *node) {
		if (node->symbol == WASM_IMMEDIATE)
			return dynamic_cast<WASMImmediateNode *>(node)->imm;
		if (node->symbol == WASMTOK_NUMBER)
			return static_cast<int>(node->atoi());
		if (node->symbol == WASMTOK_CHAR) {
			const std::string middle = node->lexerInfo->substr(1, node->lexerInfo->size() - 2);
			if (middle.size() == 1)
				return middle.front();
			if (middle.front() != '\\') {
				if (middle == "$(")
					return '{';
				if (middle == "$)")
					return '}';
				throw std::runtime_error("Invalid character literal: " + *node->lexerInfo);
			}
			size_t pos = middle.find_first_not_of("\\");
			if (pos == std::string::npos)
				return '\\';
			switch (middle[pos]) {
				case 'n': return '\n';
				case 'r': return '\r';
				case 'a': return '\a';
				case 't': return '\t';
				case 'b': return '\b';
				default:  throw std::runtime_error("Invalid character literal: " + *node->lexerInfo);
			}
		}
		if (node->symbol == WASMTOK_STRING)
			return node->extracted();
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
		return colorize(imm);
	}

	WASMImmediateNode::operator std::string() const {
		return toString(imm);
	}

	WASMLabelNode::WASMLabelNode(ASTNode *label_): WASMInstructionNode(WASM_LABEL), label(label_->lexerInfo) {
		delete label_;
	}

	std::string WASMLabelNode::debugExtra() const {
		return cyan("@") + "\e[38;5;202m" + *label + "\e[39m";
	}

	WASMLabelNode::operator std::string() const {
		return "@" + *label;
	}

	std::unique_ptr<WhyInstruction> WASMLabelNode::convert(Function &, VarMap &) {
		return std::make_unique<Label>(*label);
	}

	RNode::RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_):
	WASMInstructionNode(WASM_RNODE), rs(rs_->lexerInfo), oper(oper_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo),
	operToken(oper_->symbol), isUnsigned(!!unsigned_) {
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
			case WASMTOK_PERCENT:
				if (isUnsigned) return std::make_unique<ModuRInstruction>(conv(rs), conv(rt), conv(rd));
				return std::make_unique<ModRInstruction>(conv(rs), conv(rt), conv(rd));
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
			case WASMTOK_NOT:
				return std::make_unique<NotRInstruction>(conv(rs), conv(rd));
			case WASMTOK_MEMSET:
				return std::make_unique<MemsetInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_LL:
				return std::make_unique<ShiftLeftLogicalRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_RL:
				return std::make_unique<ShiftRightLogicalRInstruction>(conv(rs), conv(rt), conv(rd));
			case WASMTOK_RA:
				return std::make_unique<ShiftRightArithmeticRInstruction>(conv(rs), conv(rt), conv(rd));
			default:
				throw std::invalid_argument("Unknown operator in RNode::convert: " + *oper);
		}
	}

	INode::INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm_, ASTNode *rd_, ASTNode *unsigned_):
	WASMInstructionNode(WASM_INODE), rs(rs_->lexerInfo), oper(oper_->lexerInfo), rd(rd_->lexerInfo),
	operToken(oper_->symbol), imm(getImmediate(imm_)), isUnsigned(!!unsigned_) {
		delete rs_;
		delete oper_;
		delete imm_;
		delete rd_;
		if (unsigned_)
			delete unsigned_;
	}

	std::string INode::debugExtra() const {
		return cyan(*rs) + " " + dim(*oper) + " " + colorize(imm) + dim(" -> ") + cyan(*rd) + (isUnsigned? " /u" : "");
	}

	INode::operator std::string() const {
		return *rs + " " + *oper + " " + toString(imm) + " -> " + *rd + (isUnsigned? " /u" : "");
	}

	std::unique_ptr<WhyInstruction> INode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };

		switch (operToken) {
			case WASMTOK_PERCENT:
				if (isUnsigned) return std::make_unique<ModuIInstruction>(conv(rs), imm, conv(rd));
				return std::make_unique<ModIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_SLASH:
				if (isUnsigned) return std::make_unique<DivuIInstruction>(conv(rs), imm, conv(rd));
				return std::make_unique<DivIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_LANGLE:
				return std::make_unique<ComparisonIInstruction>(conv(rs), imm, conv(rd),
					isUnsigned? IcmpCond::Ult : IcmpCond::Slt);
			case WASMTOK_LEQ:
				return std::make_unique<ComparisonIInstruction>(conv(rs), imm, conv(rd),
					isUnsigned? IcmpCond::Ule : IcmpCond::Sle);
			case WASMTOK_DEQ:
				return std::make_unique<ComparisonIInstruction>(conv(rs), imm, conv(rd), IcmpCond::Eq);
			case WASMTOK_RANGLE:
				return std::make_unique<ComparisonIInstruction>(conv(rs), imm, conv(rd),
					isUnsigned? IcmpCond::Ugt : IcmpCond::Sgt);
			case WASMTOK_GEQ:
				return std::make_unique<ComparisonIInstruction>(conv(rs), imm, conv(rd),
					isUnsigned? IcmpCond::Uge : IcmpCond::Sge);
			case WASMTOK_AND:
				return std::make_unique<AndIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_OR:
				return std::make_unique<OrIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_X:
				return std::make_unique<XorIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_NAND:
				return std::make_unique<NandIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_NOR:
				return std::make_unique<NorIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_XNOR:
				return std::make_unique<XnorIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_LAND:
				return std::make_unique<LogicalAndIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_LOR:
				return std::make_unique<LogicalOrIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_LXOR:
				return std::make_unique<LogicalXorIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_LNAND:
				return std::make_unique<LogicalNandIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_LNOR:
				return std::make_unique<LogicalNorIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_LXNOR:
				return std::make_unique<LogicalXnorIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_PLUS:
				return std::make_unique<AddIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_MINUS:
				return std::make_unique<SubIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_LL:
				return std::make_unique<ShiftLeftLogicalIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_RL:
				return std::make_unique<ShiftRightLogicalIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_RA:
				return std::make_unique<ShiftRightArithmeticIInstruction>(conv(rs), imm, conv(rd));
			default:
				throw std::invalid_argument("Unknown operator in INode::convert: " + *oper);
		}
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

	std::unique_ptr<WhyInstruction> WASMCopyNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<CopyRInstruction>(conv(rs), conv(rd), isByte? 1 : 8);
	}

	WASMLoadNode::WASMLoadNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMMemoryNode(WASM_LOADNODE, rs_, rd_, byte_) {}

	std::string WASMLoadNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> ") + cyan(*rd) + (isByte? " /b" : "");
	}

	WASMLoadNode::operator std::string() const {
		return "[" + *rs + "] -> " + *rd + (isByte? " /b" : "");
	}

	std::unique_ptr<WhyInstruction> WASMLoadNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<LoadRInstruction>(conv(rs), conv(rd), isByte? 1 : 8);
	}

	WASMStoreNode::WASMStoreNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMMemoryNode(WASM_STORENODE, rs_, rd_, byte_) {}

	std::string WASMStoreNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + cyan(*rd) + dim("]") + (isByte? " /b" : "");
	}

	WASMStoreNode::operator std::string() const {
		return *rs + " -> [" + *rd + "]" + (isByte? " /b" : "");
	}

	std::unique_ptr<WhyInstruction> WASMStoreNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<StoreRInstruction>(conv(rs), conv(rd), isByte? 1 : 8);
	}

	WASMSetNode::WASMSetNode(ASTNode *imm_, ASTNode *rd_):
	WASMInstructionNode(WASM_SETNODE), rd(rd_->lexerInfo), imm(getImmediate(imm_)) {
		delete imm_;
		delete rd_;
	}

	std::string WASMSetNode::debugExtra() const {
		return colorize(imm) + dim(" -> ") + cyan(*rd);
	}

	WASMSetNode::operator std::string() const {
		return toString(imm) + " -> " + *rd;
	}

	std::unique_ptr<WhyInstruction> WASMSetNode::convert(Function &function, VarMap &map) {
		return std::make_unique<SetInstruction>(convertVariable(function, map, rd), imm);
	}

	WASMLiNode::WASMLiNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_):
	WASMInstructionNode(WASM_LINODE), rd(rd_->lexerInfo), imm(getImmediate(imm_)), isByte(!!byte_) {
		delete imm_;
		delete rd_;
		if (byte_)
			delete byte_;
	}

	std::string WASMLiNode::debugExtra() const {
		return dim("[") + colorize(imm) + dim("] -> ") + cyan(*rd) + (isByte? " /b" : "");
	}

	WASMLiNode::operator std::string() const {
		return "[" + toString(imm) + "] -> " + *rd + (isByte? " /b" : "");
	}

	std::unique_ptr<WhyInstruction> WASMLiNode::convert(Function &function, VarMap &map) {
		return std::make_unique<LoadIInstruction>(imm, convertVariable(function, map, rd), isByte? 1 : 8);
	}

	WASMSiNode::WASMSiNode(ASTNode *rs_, ASTNode *imm_, ASTNode *byte_):
	WASMInstructionNode(WASM_SINODE), rs(rs_->lexerInfo), imm(getImmediate(imm_)), isByte(!!byte_) {
		delete rs_;
		delete imm_;
		if (byte_)
			delete byte_;
	}

	std::string WASMSiNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + colorize(imm) + dim("]") + (isByte? " /b" : "");
	}

	WASMSiNode::operator std::string() const {
		return *rs + " -> [" + toString(imm) + "]" + (isByte? " /b" : "");
	}

	std::unique_ptr<WhyInstruction> WASMSiNode::convert(Function &function, VarMap &map) {
		return std::make_unique<StoreIInstruction>(convertVariable(function, map, rs), imm, isByte? 1 : 8);
	}

	WASMLniNode::WASMLniNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_): WASMLiNode(imm_, rd_, byte_) {
		symbol = WASM_LNINODE;
	}

	std::string WASMLniNode::debugExtra() const {
		return dim("[") + colorize(imm) + dim("] -> [") + cyan(*rd) + dim("]") + (isByte? " /b" : "");
	}

	WASMLniNode::operator std::string() const {
		return "[" + toString(imm) + "] -> [" + *rd + "]" + (isByte? " /b" : "");
	}

	std::unique_ptr<WhyInstruction> WASMLniNode::convert(Function &function, VarMap &map) {
		return std::make_unique<LoadIndirectIInstruction>(imm, convertVariable(function, map, rd), isByte? 1 : 8);
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

	std::unique_ptr<WhyInstruction> WASMChNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<CopyRInstruction>(conv(rs), conv(rd), 4);
	}

	WASMLhNode::WASMLhNode(ASTNode *rs_, ASTNode *rd_):
		WASMHalfMemoryNode(WASM_LHNODE, rs_, rd_) {}

	std::string WASMLhNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> ") + cyan(*rd) + " /h";
	}

	WASMLhNode::operator std::string() const {
		return "[" + *rs + "] -> " + *rd + " /h";
	}

	std::unique_ptr<WhyInstruction> WASMLhNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<LoadRInstruction>(conv(rs), conv(rd), 4);
	}

	WASMShNode::WASMShNode(ASTNode *rs_, ASTNode *rd_):
		WASMHalfMemoryNode(WASM_SHNODE, rs_, rd_) {}

	std::string WASMShNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + cyan(*rd) + dim("]") + " /h";
	}

	WASMShNode::operator std::string() const {
		return *rs + " -> [" + *rd + "] /h";
	}

	std::unique_ptr<WhyInstruction> WASMShNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<StoreRInstruction>(conv(rs), conv(rd), 4);
	}

	WASMCmpNode::WASMCmpNode(ASTNode *rs_, ASTNode *rt_):
	WASMInstructionNode(WASM_CMPNODE), rs(rs_->lexerInfo), rt(rt_->lexerInfo) {
		delete rs_;
		delete rt_;
	}

	std::string WASMCmpNode::debugExtra() const {
		return cyan(*rs) + dim(" ~ ") + cyan(*rt);
	}

	WASMCmpNode::operator std::string() const {
		return *rs + " ~ " + *rt;
	}

	std::unique_ptr<WhyInstruction> WASMCmpNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<CompareRInstruction>(conv(rs), conv(rt));
	}

	WASMCmpiNode::WASMCmpiNode(ASTNode *rs_, ASTNode *imm_):
	WASMInstructionNode(WASM_CMPINODE), rs(rs_->lexerInfo), imm(getImmediate(imm_)) {
		delete rs_;
		delete imm_;
	}

	std::string WASMCmpiNode::debugExtra() const {
		return cyan(*rs) + dim(" ~ ") + colorize(imm);
	}

	WASMCmpiNode::operator std::string() const {
		return *rs + " ~ " + toString(imm);
	}

	std::unique_ptr<WhyInstruction> WASMCmpiNode::convert(Function &function, VarMap &map) {
		return std::make_unique<CompareIInstruction>(convertVariable(function, map, rs), imm);
	}

	WASMSelNode::WASMSelNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_):
	WASMInstructionNode(WASM_SELNODE), rs(rs_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo) {
		delete rs_;
		delete rt_;
		delete rd_;
		if (*oper_->lexerInfo == "=")
			condition = Condition::Zero;
		else if (*oper_->lexerInfo == "<")
			condition = Condition::Negative;
		else if (*oper_->lexerInfo == ">")
			condition = Condition::Positive;
		else if (*oper_->lexerInfo == "!=")
			condition = Condition::Nonzero;
		else
			wasmerror("Invalid operator: " + *oper_->lexerInfo);
		delete oper_;
	}

	std::string WASMSelNode::debugExtra() const {
		const char *oper_;
		switch (condition) {
			case Condition::Zero:     oper_ = "=";  break;
			case Condition::Negative: oper_ = "<";  break;
			case Condition::Positive: oper_ = ">";  break;
			case Condition::Nonzero:  oper_ = "!="; break;
			default:
				throw std::runtime_error("Invalid operator in WASMSelNode: " +
					std::to_string(static_cast<int>(condition)));
		}
		return dim("[") + cyan(*rs) + " " + dim(oper_) + " " + cyan(*rt) + dim("] -> ") + cyan(*rd);
	}

	WASMSelNode::operator std::string() const {
		const char *oper_;
		switch (condition) {
			case Condition::Zero:     oper_ = "=";  break;
			case Condition::Negative: oper_ = "<";  break;
			case Condition::Positive: oper_ = ">";  break;
			case Condition::Nonzero:  oper_ = "!="; break;
			default:
				throw std::runtime_error("Invalid operator in WASMSelNode: " +
					std::to_string(static_cast<int>(condition)));
		}
		return "[" + *rs + " " + oper_ + " " + *rt + "] -> " + *rd;
	}

	std::unique_ptr<WhyInstruction> WASMSelNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<SelectInstruction>(conv(rs), conv(rt), conv(rd), condition);
	}

	WASMJNode::WASMJNode(ASTNode *cond, ASTNode *colons, ASTNode *addr_):
	WASMInstructionNode(WASM_JNODE), addr(getImmediate(addr_)), link(!colons->empty()) {
		delete addr_;
		delete colons;
		if (!cond) {
			condition = Condition::None;
		} else {
			condition = getCondition(*cond->lexerInfo);
			delete cond;
		}
	}

	std::string WASMJNode::debugExtra() const {
		return dim(conditionString(condition) + std::string(link? "::" : ":")) + " " + colorize(addr);
	}

	WASMJNode::operator std::string() const {
		return conditionString(condition) + std::string(link? "::" : ":") + " " + toString(addr);
	}

	std::unique_ptr<WhyInstruction> WASMJNode::convert(Function &, VarMap &) {
		return std::make_unique<JumpInstruction>(addr, link, condition);
	}

	WASMJcNode::WASMJcNode(WASMJNode *j, ASTNode *rs_):
	WASMInstructionNode(WASM_JCNODE), link(j? j->link : false), addr(j? j->addr : 0), rs(rs_->lexerInfo) {
		if (!j) {
			wasmerror("No WASMCJNode found in jc instruction");
		} else {
			if (j->condition != Condition::None)
				wasmerror("Conditions specified for jc instruction will be ignored");
			delete j;
		}
		delete rs_;
	}

	std::string WASMJcNode::debugExtra() const {
		return dim(link? "::" : ":") + " " + colorize(addr) + red(" if ") + cyan(*rs);
	}

	WASMJcNode::operator std::string() const {
		return std::string(link? "::" : ":") + " " + toString(addr) + " if " + *rs;
	}

	std::unique_ptr<WhyInstruction> WASMJcNode::convert(Function &function, VarMap &map) {
		return std::make_unique<JumpConditionalInstruction>(convertVariable(function, map, rs), addr, link);
	}

	WASMJrNode::WASMJrNode(ASTNode *cond, ASTNode *colons, ASTNode *rd_):
	WASMInstructionNode(WASM_JRNODE), link(!colons->empty()), rd(rd_->lexerInfo) {
		delete colons;
		delete rd_;
		if (!cond) {
			condition = Condition::None;
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

	std::unique_ptr<WhyInstruction> WASMJrNode::convert(Function &function, VarMap &map) {
		return std::make_unique<JumpRegisterInstruction>(convertVariable(function, map, rd), false, condition);
	}

	WASMJrcNode::WASMJrcNode(WASMJrNode *jr, ASTNode *rs_):
	WASMInstructionNode(WASM_JRCNODE), link(jr? jr->link : false), rs(rs_->lexerInfo), rd(jr? jr->rd : nullptr) {
		if (!jr) {
			wasmerror("No WASMCJrNode found in jr(l)c instruction");
		} else {
			if (jr->condition != Condition::None)
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

	std::unique_ptr<WhyInstruction> WASMJrcNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<JumpRegisterConditionalInstruction>(conv(rs), conv(rd), link);
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

	std::unique_ptr<WhyInstruction> WASMSizedStackNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		if (isPush)
			return std::make_unique<SizedStackPushInstruction>(conv(rs), size);
		return std::make_unique<SizedStackPopInstruction>(conv(rs), size);
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

	std::unique_ptr<WhyInstruction> WASMMultRNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<MultRInstruction>(conv(rs), conv(rt));
	}

	WASMMultINode::WASMMultINode(ASTNode *rs_, ASTNode *imm_, ASTNode *unsigned_):
	WASMInstructionNode(WASM_MULTINODE), rs(rs_->lexerInfo), imm(getImmediate(imm_)), isUnsigned(!!unsigned_) {
		delete rs_;
		delete imm_;
		if (unsigned_)
			delete unsigned_;
	}

	std::string WASMMultINode::debugExtra() const {
		return cyan(*rs) + dim(" * ") + colorize(imm) + (isUnsigned? " /u" : "");
	};

	WASMMultINode::operator std::string() const {
		return *rs + " * " + toString(imm) + (isUnsigned? " /u" : "");
	}

	std::unique_ptr<WhyInstruction> WASMMultINode::convert(Function &function, VarMap &map) {
		return std::make_unique<MultIInstruction>(convertVariable(function, map, rs), imm);
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
		return colorize(imm) + dim(" / ") + cyan(*rs) + dim(" -> ") + cyan(*rd) + (isUnsigned? " /u" : "");
	}

	WASMDiviINode::operator std::string() const {
		return toString(imm) + " / " + *rs + " -> " + *rd + (isUnsigned? " /u" : "");
	}

	std::unique_ptr<WhyInstruction> WASMDiviINode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<DiviIInstruction>(conv(rs), imm, conv(rd));
	}

	WASMLuiNode::WASMLuiNode(ASTNode *imm_, ASTNode *rd_):
	WASMInstructionNode(WASM_LUINODE), rd(rd_->lexerInfo), imm(getImmediate(imm_)) {
		delete imm_;
		delete rd_;
	}

	std::string WASMLuiNode::debugExtra() const {
		return "lui" + dim(": ") + colorize(imm) + dim(" -> ") + cyan(*rd);
	}

	WASMLuiNode::operator std::string() const {
		return "lui: " + toString(imm) + " -> " + *rd;
	}

	std::unique_ptr<WhyInstruction> WASMLuiNode::convert(Function &function, VarMap &map) {
		return std::make_unique<LuiInstruction>(convertVariable(function, map, rd), imm);
	}

	WASMStackNode::WASMStackNode(ASTNode *reg_, bool is_push):
	WASMInstructionNode(WASM_STACKNODE), reg(reg_->lexerInfo), isPush(is_push) {
		delete reg_;
	}

	std::string WASMStackNode::debugExtra() const {
		return dim(isPush? "[" : "]") + " " + cyan(*reg);
	}

	WASMStackNode::operator std::string() const {
		return std::string(isPush? "[" : "]") + " " + *reg;
	}

	std::unique_ptr<WhyInstruction> WASMStackNode::convert(Function &function, VarMap &map) {
		if (isPush)
			return std::make_unique<StackPushInstruction>(convertVariable(function, map, reg));
		return std::make_unique<StackPopInstruction>(convertVariable(function, map, reg));
	}

	WASMNopNode::WASMNopNode(): WASMInstructionNode(WASM_NOPNODE) {}

	std::string WASMNopNode::debugExtra() const {
		return dim("<>");
	}

	WASMNopNode::operator std::string() const {
		return "<>";
	}

	std::unique_ptr<WhyInstruction> WASMNopNode::convert(Function &, VarMap &) {
		return std::make_unique<Nop>();
	}

	WASMIntINode::WASMIntINode(ASTNode *imm_): WASMInstructionNode(WASM_INTINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMIntINode::debugExtra() const {
		return blue("int") + " " + colorize(imm);
	}

	WASMIntINode::operator std::string() const {
		return "int " + toString(imm);
	}

	std::unique_ptr<WhyInstruction> WASMIntINode::convert(Function &, VarMap &) {
		return std::make_unique<IntIInstruction>(imm);
	}

	WASMRitINode::WASMRitINode(ASTNode *imm_): WASMInstructionNode(WASM_RITINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMRitINode::debugExtra() const {
		return blue("rit") + " " + colorize(imm);
	}

	WASMRitINode::operator std::string() const {
		return "rit " + toString(imm);
	}

	std::unique_ptr<WhyInstruction> WASMRitINode::convert(Function &, VarMap &) {
		return std::make_unique<RitIInstruction>(imm);
	}

	WASMTimeINode::WASMTimeINode(ASTNode *imm_): WASMInstructionNode(WASM_TIMEINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMTimeINode::debugExtra() const {
		return blue("time") + " " + colorize(imm);
	}

	WASMTimeINode::operator std::string() const {
		return "time " + toString(imm);
	}

	std::unique_ptr<WhyInstruction> WASMTimeINode::convert(Function &, VarMap &) {
		return std::make_unique<TimeIInstruction>(imm);
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

	std::unique_ptr<WhyInstruction> WASMTimeRNode::convert(Function &function, VarMap &map) {
		return std::make_unique<TimeRInstruction>(convertVariable(function, map, rs));
	}

	WASMRingINode::WASMRingINode(ASTNode *imm_): WASMInstructionNode(WASM_RINGINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMRingINode::debugExtra() const {
		return blue("ring") + " " + colorize(imm);
	}

	WASMRingINode::operator std::string() const {
		return "ring " + toString(imm);
	}

	std::unique_ptr<WhyInstruction> WASMRingINode::convert(Function &, VarMap &) {
		return std::make_unique<RingIInstruction>(imm);
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

	std::unique_ptr<WhyInstruction> WASMRingRNode::convert(Function &function, VarMap &map) {
		return std::make_unique<RingRInstruction>(convertVariable(function, map, rs));
	}

	WASMPrintNode::WASMPrintNode(ASTNode *rs_, ASTNode *type_):
	WASMInstructionNode(WASM_PRINTNODE), rs(rs_->lexerInfo) {
		delete rs_;
		const std::string &typestr = *type_->lexerInfo;
		if (typestr == "prx")
			type = PrintType::Hex;
		else if (typestr == "prd")
			type = PrintType::Dec;
		else if (typestr == "prc")
			type = PrintType::Char;
		else if (typestr == "print")
			type = PrintType::Full;
		else if (typestr == "prb")
			type = PrintType::Bin;
		else {
			wasmerror("Invalid print type: " + typestr);
			type = PrintType::Full;
		}
		delete type_;
	}

	std::string WASMPrintNode::debugExtra() const {
		switch (type) {
			case PrintType::Hex:  return "<" + blue("prx")   + " " + cyan(*rs) + ">";
			case PrintType::Dec:  return "<" + blue("prd")   + " " + cyan(*rs) + ">";
			case PrintType::Char: return "<" + blue("prc")   + " " + cyan(*rs) + ">";
			case PrintType::Full: return "<" + blue("print") + " " + cyan(*rs) + ">";
			case PrintType::Bin:  return "<" + blue("prb")   + " " + cyan(*rs) + ">";
			default:
				return red("???");
		}
	}

	WASMPrintNode::operator std::string() const {
		switch (type) {
			case PrintType::Hex:  return "<prx "   + *rs + ">";
			case PrintType::Dec:  return "<prd "   + *rs + ">";
			case PrintType::Char: return "<prc "   + *rs + ">";
			case PrintType::Full: return "<print " + *rs + ">";
			case PrintType::Bin:  return "<prb "   + *rs + ">";
			default:
				return "???";
		}
	}

	std::unique_ptr<WhyInstruction> WASMPrintNode::convert(Function &function, VarMap &map) {
		return std::make_unique<PrintRInstruction>(convertVariable(function, map, rs), type);
	}

	WASMHaltNode::WASMHaltNode(): WASMInstructionNode(WASM_HALTNODE) {}

	std::string WASMHaltNode::debugExtra() const {
		return "<" + blue("halt") + ">";
	}

	WASMHaltNode::operator std::string() const {
		return "<halt>";
	}

	std::unique_ptr<WhyInstruction> WASMHaltNode::convert(Function &, VarMap &) {
		return std::make_unique<HaltInstruction>();
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

	std::unique_ptr<WhyInstruction> WASMSleepRNode::convert(Function &function, VarMap &map) {
		return std::make_unique<SleepRInstruction>(convertVariable(function, map, rs));
	}

	WASMPageNode::WASMPageNode(bool on_): WASMInstructionNode(WASM_PAGENODE), on(on_) {}

	std::string WASMPageNode::debugExtra() const {
		return blue("page") + " " + (on? "on" : "off");
	}

	WASMPageNode::operator std::string() const {
		return "page " + std::string(on? "on" : "off");
	}

	std::unique_ptr<WhyInstruction> WASMPageNode::convert(Function &, VarMap &) {
		return std::make_unique<PageInstruction>(on);
	}

	WASMSetptINode::WASMSetptINode(ASTNode *imm_): WASMInstructionNode(WASM_SETPTINODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	std::string WASMSetptINode::debugExtra() const {
		return blue("setpt") + " " + colorize(imm);
	}

	WASMSetptINode::operator std::string() const {
		return "setpt " + toString(imm);
	}

	std::unique_ptr<WhyInstruction> WASMSetptINode::convert(Function &, VarMap &) {
		return std::make_unique<SetptIInstruction>(imm);
	}

	WASMSetptRNode::WASMSetptRNode(ASTNode *rs_): WASMInstructionNode(WASM_SETPTRNODE), rs(rs_->lexerInfo) {
		delete rs_;
	}

	std::string WASMSetptRNode::debugExtra() const {
		return blue("setpt") + " " + cyan(*rs);
	}

	WASMSetptRNode::operator std::string() const {
		return "setpt " + *rs;
	}

	std::unique_ptr<WhyInstruction> WASMSetptRNode::convert(Function &function, VarMap &map) {
		return std::make_unique<SetptRInstruction>(convertVariable(function, map, rs));
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

	std::unique_ptr<WhyInstruction> WASMMvNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<MoveInstruction>(conv(rs), conv(rd));
	}

	WASMSvpgNode::WASMSvpgNode(ASTNode *rd_):
	WASMInstructionNode(WASM_SVPGNODE), rd(rd_->lexerInfo) {
		delete rd_;
	}

	std::string WASMSvpgNode::debugExtra() const {
		return blue("page") + dim(" -> ") + cyan(*rd);
	}

	WASMSvpgNode::operator std::string() const {
		return "page -> " + *rd;
	}

	std::unique_ptr<WhyInstruction> WASMSvpgNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };
		return std::make_unique<SvpgInstruction>(conv(rd));
	}

	WASMQueryNode::WASMQueryNode(QueryType type_, ASTNode *rd_):
	WASMInstructionNode(WASM_QUERYNODE), type(type_), rd(rd_->lexerInfo) {
		delete rd_;
	}

	std::string WASMQueryNode::debugExtra() const {
		return "? " + blue(query_map.at(type)) + dim(" -> ") + cyan(*rd);
	}

	WASMQueryNode::operator std::string() const {
		return "? mem -> " + *rd;
	}

	std::unique_ptr<WhyInstruction> WASMQueryNode::convert(Function &function, VarMap &map) {
		return std::make_unique<QueryInstruction>(type, convertVariable(function, map, rd));
	}

	WASMPseudoPrintNode::WASMPseudoPrintNode(ASTNode *imm_):
	WASMInstructionNode(WASM_PSEUDOPRINTNODE), imm(getImmediate(imm_)) {
		delete imm_;
	}

	WASMPseudoPrintNode::WASMPseudoPrintNode(const std::string *text_):
		WASMInstructionNode(WASM_PSEUDOPRINTNODE), imm(0), text(text_) {}

	std::string WASMPseudoPrintNode::debugExtra() const {
		return "<" + blue("p") + " " + (text? *text : colorize(imm)) + ">";
	}

	WASMPseudoPrintNode::operator std::string() const {
		return "<p " + (text? *text : toString(imm)) + ">";
	}

	std::unique_ptr<WhyInstruction> WASMPseudoPrintNode::convert(Function &, VarMap &) {
		if (text)
			return std::make_unique<PrintPseudoinstruction>(text, true, -1);
		return std::make_unique<PrintPseudoinstruction>(imm, -1);
	}

	WASMRestNode::WASMRestNode(): WASMInstructionNode(WASM_RESTNODE) {}

	std::string WASMRestNode::debugExtra() const {
		return "<" + blue("rest") + ">";
	}

	WASMRestNode::operator std::string() const {
		return "<rest>";
	}

	std::unique_ptr<WhyInstruction> WASMRestNode::convert(Function &, VarMap &) {
		return std::make_unique<RestInstruction>();
	}

	WASMIONode::WASMIONode(const std::string *ident_): WASMInstructionNode(WASM_IONODE), ident(ident_) {}

	std::string WASMIONode::debugExtra() const {
		return ident? "<" + blue("io") + " " + *ident + ">" : "<" + blue("io") + ">";
	}

	WASMIONode::operator std::string() const {
		return ident? "<io " + *ident + ">" : "<io>";
	}

	std::unique_ptr<WhyInstruction> WASMIONode::convert(Function &, VarMap &) {
		return std::make_unique<IOInstruction>(ident);
	}

	WASMInterruptsNode::WASMInterruptsNode(bool enable_): WASMInstructionNode(WASM_INTERRUPTSNODE), enable(enable_) {}

	std::string WASMInterruptsNode::debugExtra() const {
		return blue(enable? "%ei" : "%di");
	}

	WASMInterruptsNode::operator std::string() const {
		return enable? "%ei" : "%di";
	}

	std::unique_ptr<WhyInstruction> WASMInterruptsNode::convert(Function &, VarMap &) {
		return std::make_unique<InterruptsInstruction>(enable);
	}

	WASMInverseShiftNode::WASMInverseShiftNode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm_, ASTNode *rd_):
	WASMInstructionNode(WASM_INVERSESHIFTNODE), rs(rs_->lexerInfo), oper(oper_->lexerInfo), rd(rd_->lexerInfo),
	operToken(oper_->symbol), imm(getImmediate(imm_)) {
		delete rs_;
		delete oper_;
		delete imm_;
		delete rd_;
	}

	std::string WASMInverseShiftNode::debugExtra() const {
		return colorize(imm) + " " + dim(*oper) + " " + cyan(*rs) + dim(" -> ") + cyan(*rd);
	}

	WASMInverseShiftNode::operator std::string() const {
		return toString(imm) + " " + *oper + " " + *rs + " -> " + *rd;
	}

	std::unique_ptr<WhyInstruction> WASMInverseShiftNode::convert(Function &function, VarMap &map) {
		auto conv = [&](const std::string *str) { return convertVariable(function, map, str); };

		switch (operToken) {
			case WASMTOK_LL:
				return std::make_unique<ShiftLeftLogicalInverseIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_RL:
				return std::make_unique<ShiftRightLogicalInverseIInstruction>(conv(rs), imm, conv(rd));
			case WASMTOK_RA:
				return std::make_unique<ShiftRightArithmeticInverseIInstruction>(conv(rs), imm, conv(rd));
			default:
				throw std::invalid_argument("Unknown operator in WASMInverseShiftNode::convert: " + *oper);
		}
	}

	WASMSextNode::WASMSextNode(ASTNode *rs_, ASTNode *rd_, ASTNode *size_):
	WASMInstructionNode(WASM_SEXTNODE), rs(rs_->lexerInfo), rd(rd_->lexerInfo) {
		delete rs_;
		delete rd_;
		switch (size_->symbol) {
			case WASMTOK_SEXT32: size = 32; break;
			case WASMTOK_SEXT16: size = 16; break;
			case WASMTOK_SEXT8:  size =  8; break;
			default:
				throw std::runtime_error("Invalid symbol for WASMSextNode size: " +
					std::string(wasmParser.getName(size_->symbol)));
		}
		delete size_;
	}

	std::string WASMSextNode::debugExtra() const {
		return bold("sext" + std::to_string(size)) + " " + cyan(*rs) + dim(" -> ") + cyan(*rd);
	}

	WASMSextNode::operator std::string() const {
		return "sext" + std::to_string(size) + " " + *rs + " -> " + *rd;
	}

	std::unique_ptr<WhyInstruction> WASMSextNode::convert(Function &function, VarMap &map) {
		VariablePtr rs_ = convertVariable(function, map, rs);
		VariablePtr rd_ = convertVariable(function, map, rd);

		switch (size) {
			case 32: return std::make_unique<Sext32RInstruction>(rs_, rd_);
			case 16: return std::make_unique<Sext16RInstruction>(rs_, rd_);
			case  8: return std::make_unique<Sext8RInstruction>(rs_, rd_);
			default:
				throw std::runtime_error("Invalid size for WASMSextNode: " + std::to_string(size));
		}
	}
}
