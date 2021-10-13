#include "compiler/Subprogram.h"
#include "parser/ASTNode.h"
#include "parser/Lexer.h"

namespace LL2W {
	Subprogram::Subprogram(const ASTNode &node) {
		for (const ASTNode *subnode: node)
			switch (subnode->symbol) {
				case LLVMTOK_NAME:
					name = *subnode->front()->lexerInfo;
					break;
				case LLVMTOK_LINKAGENAME:
					linkageName = *subnode->front()->lexerInfo;
					break;
				case LLVMTOK_SCOPE:
					scope = parseBang(*subnode->front());
					break;
				case LLVMTOK_FILE:
					file = parseBang(*subnode->front());
					break;
				case LLVMTOK_LINE:
					line = subnode->front()->atoi();
					break;
				case LLVMTOK_TYPE:
					type = parseBang(*subnode->front());
					break;
				case LLVMTOK_SCOPELINE:
					scopeLine = subnode->front()->atoi();
					break;
				case LLVMTOK_UNIT:
					unit = parseBang(*subnode->front());
					break;
				case LLVMTOK_DECLARATION:
					declaration = parseBang(*subnode->front());
					break;
				case LLVMTOK_RETAINEDNODES:
					retainedNodes = parseBang(*subnode->front());
					break;
			}
	}

	std::string Subprogram::getName() const {
		const std::string &nonempty = name.empty()? linkageName : name;
		return nonempty.substr(1, nonempty.size() - 2);
	}

	int Subprogram::parseBang(const ASTNode &node) {
		return node.symbol == LLVMTOK_INTBANG? node.atoi() : -1;
	}
}
