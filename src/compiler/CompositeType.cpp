#include "compiler/CompositeType.h"
#include "compiler/Program.h"
#include "parser/ASTNode.h"
#include "parser/Constant.h"
#include "parser/Lexer.h"

namespace LL2W {
	CompositeType::CompositeType(const ASTNode &node): LLVMType(node.front()->atoi()) {
		// node.debug();
		for (const ASTNode *item: *node.back()) {
			const ASTNode &front = *item->front();
			if (item->symbol == LLVMTOK_NAME) {
				name = front.lexerInfo;
				break;
			}
		}
	}

	CompositeType::operator std::string() {
		return '!' + std::to_string(id) + " = !DICompositeType(name: " +
			(name == nullptr? "null)" : '"' + *name + "\")");
	}
}
