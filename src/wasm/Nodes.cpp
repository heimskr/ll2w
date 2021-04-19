#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "wasm/Nodes.h"

namespace LL2W {
	RNode::RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_, ASTNode *unsigned_):
		WASMBaseNode(wasmParser, WASM_RNODE),
		rs(rs_->lexerInfo), oper(oper_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo), isUnsigned(!!unsigned_) {}

	std::string RNode::debugExtra() const {
		return *rs + " " + *oper + " " + *rt + " -> " + *rd + (isUnsigned? " /u" : "");
	}

	INode::INode(ASTNode *rs_, ASTNode *oper_, ASTNode *imm_, ASTNode *rd_, ASTNode *unsigned_):
		WASMBaseNode(wasmParser, WASM_INODE),
		rs(rs_->lexerInfo), oper(oper_->lexerInfo), rd(rd_->lexerInfo), imm(imm_->atoi()), isUnsigned(!!unsigned_) {}

	std::string INode::debugExtra() const {
		return *rs + " " + *oper + " " + std::to_string(imm) + " -> " + *rd + (isUnsigned? " /u" : "");
	}

	WASMCopyNode::WASMCopyNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMBaseNode(wasmParser, WASM_COPYNODE), rs(rs_->lexerInfo), rd(rd_->lexerInfo), isByte(!!byte_) {}

	std::string WASMCopyNode::debugExtra() const {
		return "[" + *rs + "] -> [" + *rd + "]" + (isByte? " /b" : "");
	}

	WASMLoadNode::WASMLoadNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMBaseNode(wasmParser, WASM_LOADNODE), rs(rs_->lexerInfo), rd(rd_->lexerInfo), isByte(!!byte_) {}

	std::string WASMLoadNode::debugExtra() const {
		return "[" + *rs + "] -> " + *rd + (isByte? " /b" : "");
	}

	WASMStoreNode::WASMStoreNode(ASTNode *rs_, ASTNode *rd_, ASTNode *byte_):
		WASMBaseNode(wasmParser, WASM_STORENODE), rs(rs_->lexerInfo), rd(rd_->lexerInfo), isByte(!!byte_) {}

	std::string WASMStoreNode::debugExtra() const {
		return *rs + " -> [" + *rd + "]" + (isByte? " /b" : "");
	}
}
