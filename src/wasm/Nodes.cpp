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

namespace LL2W {
	RNode::RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_):
		WASMBaseNode(wasmParser, WASM_RNODE),
		rs(rs_->lexerInfo), oper(oper_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo), isUnsigned(!!unsigned_) {}

	std::string RNode::debugExtra() const {
		return cyan(*rs) + " " + dim(*oper) + " " + cyan(*rt) + dim(" -> ") + cyan(*rd) + (isUnsigned? " /u" : "");
	}

	INode::INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm_, ASTNode *rd_, ASTNode *unsigned_):
		WASMBaseNode(wasmParser, WASM_INODE),
		rs(rs_->lexerInfo), oper(oper_->lexerInfo), rd(rd_->lexerInfo), imm(imm_->atoi()), isUnsigned(!!unsigned_) {}

	std::string INode::debugExtra() const {
		return cyan(*rs) + " " + dim(*oper) + " " + green(std::to_string(imm)) + dim(" -> ") + cyan(*rd)
		     + (isUnsigned? " /u" : "");
	}

	WASMMemoryNode::WASMMemoryNode(int token, ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMBaseNode(wasmParser, token), rs(rs_->lexerInfo), rd(rd_->lexerInfo), isByte(!!byte_) {}

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
		WASMBaseNode(wasmParser, WASM_SETNODE), rd(rd_->lexerInfo), imm(imm_->atoi()) {}

	std::string WASMSetNode::debugExtra() const {
		return green(std::to_string(imm)) + dim(" -> ") + cyan(*rd);
	}

	WASMLiNode::WASMLiNode(ASTNode *imm_, ASTNode *rd_, ASTNode *byte_):
		WASMBaseNode(wasmParser, WASM_LINODE), rd(rd_->lexerInfo), imm(imm_->atoi()), isByte(!!byte_) {}

	std::string WASMLiNode::debugExtra() const {
		return dim("[") + green(std::to_string(imm)) + dim("] -> ") + cyan(*rd) + (isByte? " /b" : "");
	}
}
