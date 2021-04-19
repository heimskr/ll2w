#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "wasm/Nodes.h"

namespace LL2W {
	RNode::RNode(ASTNode *rs_, ASTNode *oper_, ASTNode *rt_, ASTNode *rd_):
		WASMBaseNode(wasmParser, WASM_RNODE),
		rs(rs_->lexerInfo), oper(oper_->lexerInfo), rt(rt_->lexerInfo), rd(rd_->lexerInfo) {}

	std::string RNode::debugExtra() const {
		return *rs + " " + *oper + " " + *rt + " -> " + *rd;
	}
}
