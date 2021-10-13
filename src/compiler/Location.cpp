#include "compiler/Location.h"
#include "parser/ASTNode.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"

namespace LL2W {
	Location::Location(const ASTNode &node) {
		for (const ASTNode *item: node)
			switch (item->symbol) {
				case LLVMTOK_LINE:      line   = item->front()->atoi(); break;
				case LLVMTOK_COLUMN:    column = item->front()->atoi(); break;
				case LLVMTOK_SCOPE:     scope  = item->front()->atoi(); break;
				case LLVMTOK_INLINEDAT: break; // I don't really care about this one.
				default:
					throw std::runtime_error("Invalid symbol in DILocation item: " +
						std::string(llvmParser.getName(item->symbol)));
			}
	}
}