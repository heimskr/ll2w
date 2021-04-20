#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "wasm/Nodes.h"

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

namespace LL2W {
	WASMBaseNode::WASMBaseNode(int sym): ASTNode(wasmParser, sym) {}

	RNode::RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_):
	WASMBaseNode(WASM_RNODE),
	rs(rs_->lexerInfo), oper(oper_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo), isUnsigned(!!unsigned_) {
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

	INode::INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm_, ASTNode *rd_, ASTNode *unsigned_):
	WASMBaseNode(WASM_INODE),
	rs(rs_->lexerInfo), oper(oper_->lexerInfo), rd(rd_->lexerInfo), imm(imm_->atoi()), isUnsigned(!!unsigned_) {
		delete rs_;
		delete oper_;
		delete imm_;
		delete rd_;
		if (unsigned_)
			delete unsigned_;
	}

	std::string INode::debugExtra() const {
		return cyan(*rs) + " " + dim(*oper) + " " + green(std::to_string(imm)) + dim(" -> ") + cyan(*rd)
		     + (isUnsigned? " /u" : "");
	}

	WASMMemoryNode::WASMMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
	WASMBaseNode(sym), rs(rs_->lexerInfo), rd(rd_->lexerInfo), isByte(!!byte_) {
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

	WASMLoadNode::WASMLoadNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMMemoryNode(WASM_LOADNODE, rs_, rd_, byte_) {}

	std::string WASMLoadNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> ") + cyan(*rd) + (isByte? " /b" : "");
	}

	WASMStoreNode::WASMStoreNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMMemoryNode(WASM_STORENODE, rs_, rd_, byte_) {}

	std::string WASMStoreNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + cyan(*rd) + dim("]") + (isByte? " /b" : "");
	}

	WASMSetNode::WASMSetNode(ASTNode *imm_, ASTNode *rd_):
	WASMBaseNode(WASM_SETNODE), rd(rd_->lexerInfo), imm(imm_->atoi()) {
		delete imm_;
		delete rd_;
	}

	std::string WASMSetNode::debugExtra() const {
		return green(std::to_string(imm)) + dim(" -> ") + cyan(*rd);
	}

	WASMLiNode::WASMLiNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_):
	WASMBaseNode(WASM_LINODE), rd(rd_->lexerInfo), imm(imm_->atoi()), isByte(!!byte_) {
		delete imm_;
		delete rd_;
		if (byte_)
			delete byte_;
	}

	std::string WASMLiNode::debugExtra() const {
		return dim("[") + green(std::to_string(imm)) + dim("] -> ") + cyan(*rd) + (isByte? " /b" : "");
	}

	WASMSiNode::WASMSiNode(ASTNode *rs_, ASTNode *imm_, ASTNode *byte_):
	WASMBaseNode(WASM_SINODE), rs(rs_->lexerInfo), imm(imm_->atoi()), isByte(!!byte_) {
		delete rs_;
		delete imm_;
		if (byte_)
			delete byte_;
	}

	std::string WASMSiNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + green(std::to_string(imm)) + dim("]") + (isByte? " /b" : "");
	}

	WASMLniNode::WASMLniNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_): WASMLiNode(imm_, rd_, byte_) {
		symbol = WASM_LNINODE;
	}

	std::string WASMLniNode::debugExtra() const {
		return dim("[") + green(std::to_string(imm)) + dim("] -> [") + cyan(*rd) + dim("]") + (isByte? " /b" : "");
	}

	WASMHalfMemoryNode::WASMHalfMemoryNode(int sym, ASTNode *rs_, ASTNode *rd_):
	WASMBaseNode(sym), rs(rs_->lexerInfo), rd(rd_->lexerInfo) {
		delete rs_;
		delete rd_;
	}

	WASMChNode::WASMChNode(ASTNode *rs_, ASTNode *rd_):
		WASMHalfMemoryNode(WASM_CHNODE, rs_, rd_) {}

	std::string WASMChNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> [") + cyan(*rd) + dim("]") + " /h";
	}

	WASMLhNode::WASMLhNode(ASTNode *rs_, ASTNode *rd_):
		WASMHalfMemoryNode(WASM_LHNODE, rs_, rd_) {}

	std::string WASMLhNode::debugExtra() const {
		return dim("[") + cyan(*rs) + dim("] -> ") + cyan(*rd) + " /h";
	}

	WASMShNode::WASMShNode(ASTNode *rs_, ASTNode *rd_):
		WASMHalfMemoryNode(WASM_SHNODE, rs_, rd_) {}

	std::string WASMShNode::debugExtra() const {
		return cyan(*rs) + dim(" -> [") + cyan(*rd) + dim("]") + " /h";
	}

	WASMCmpNode::WASMCmpNode(ASTNode *rs_, ASTNode *rd_):
	WASMBaseNode(WASM_CMPNODE), rs(rs_->lexerInfo), rd(rd_->lexerInfo) {
		delete rs_;
		delete rd_;
	}

	std::string WASMCmpNode::debugExtra() const {
		return cyan(*rs) + dim(" ~ ") + cyan(*rd);
	}

	WASMCmpiNode::WASMCmpiNode(ASTNode *rs_, ASTNode *imm_):
	WASMBaseNode(WASM_CMPINODE), rs(rs_->lexerInfo), imm(imm_->atoi()) {
		delete rs_;
		delete imm_;
	}

	std::string WASMCmpiNode::debugExtra() const {
		return cyan(*rs) + dim(" ~ ") + green(std::to_string(imm));
	}

	WASMSelNode::WASMSelNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_):
	WASMBaseNode(WASM_SELNODE), rs(rs_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo) {
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

	WASMJNode::WASMJNode(ASTNode *cond, ASTNode *colons, ASTNode *addr_):
	WASMBaseNode(WASM_JNODE), addr(addr_->atoi()), link(!colons->empty()) {
		delete addr_;
		delete colons;
		if (!cond) {
			condition = WASMCondition::None;
		} else {
			if (*cond->lexerInfo == "0")
				condition = WASMCondition::Zero;
			else if (*cond->lexerInfo == "+")
				condition = WASMCondition::Positive;
			else if (*cond->lexerInfo == "-")
				condition = WASMCondition::Negative;
			else if (*cond->lexerInfo == "*")
				condition = WASMCondition::NonZero;
			else
				wasmerror("Invalid condition: " + *cond->lexerInfo);
			delete cond;
		}
	}

	std::string WASMJNode::debugExtra() const {
		const char *cond;
		switch (condition) {
			case WASMCondition::None:     cond = "";  break;
			case WASMCondition::Zero:     cond = "0"; break;
			case WASMCondition::Positive: cond = "+"; break;
			case WASMCondition::Negative: cond = "-"; break;
			case WASMCondition::NonZero:  cond = "*"; break;
			default:
				throw std::runtime_error("Invalid condition in WASMJNode: "
					+ std::to_string(static_cast<int>(condition)));
		}

		return dim(cond + std::string(link? "::" : ":")) + " " + green(std::to_string(addr));
	}

	WASMJcNode::WASMJcNode(WASMJNode *j, ASTNode *rs_):
	WASMBaseNode(WASM_JCNODE), link(j? j->link : false), addr(j? j->addr : 0), rs(rs_->lexerInfo) {
		if (!j) {
			wasmerror("No WASMCJNode found in jc instruction");
		} else {
			if (j->condition != WASMCondition::None)
				wasmerror("Conditions specified for jc instruction");
			delete j;
		}
		delete rs_;
	}

	std::string WASMJcNode::debugExtra() const {
		return dim(link? "::" : ":") + " " + green(std::to_string(addr)) + red(" if ") + cyan(*rs);
	}
}
