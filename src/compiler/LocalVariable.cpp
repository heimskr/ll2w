#include <iomanip>

#include "compiler/LocalVariable.h"
#include "parser/ASTNode.h"
#include "parser/Lexer.h"
#include "parser/StringSet.h"
#include "util/Util.h"

namespace LL2W {
	LocalVariable::LocalVariable(const ASTNode &node): id(node.front()->atoi()) {
		static const std::string *nullstr = StringSet::intern("null");

		for (const ASTNode *subnode: *node.back())
			switch (subnode->symbol) {
				case LLVMTOK_NAME:
					name = subnode->front()->lexerInfo;
					break;
				case LLVMTOK_ARG:
					arg = subnode->front()->atoi();
					break;
				case LLVMTOK_SCOPE:
					if (subnode->front()->lexerInfo != nullstr)
						scope = subnode->front()->atoi();
					break;
				case LLVMTOK_FILE:
					if (subnode->front()->lexerInfo != nullstr)
						file = subnode->front()->atoi();
					break;
				case LLVMTOK_LINE:
					line = subnode->front()->atoi();
					break;
				case LLVMTOK_TYPE:
					if (subnode->front()->lexerInfo != nullstr)
						type = subnode->front()->atoi();
					break;
				case LLVMTOK_FLAGS:
					for (const ASTNode *pipe: *subnode->front())
						flags.insert(pipe->lexerInfo);
					break;
			}
	}
}
