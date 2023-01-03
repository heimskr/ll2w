#include "compiler/CompositeType.h"
#include "compiler/Program.h"
#include "parser/ASTNode.h"
#include "parser/Constant.h"
#include "parser/Lexer.h"

namespace LL2W {
	CompositeType::CompositeType(const ASTNode &node): id(node.front()->atoi()) {
		// node.debug();
		for (const ASTNode *item: *node.back()) {
			const ASTNode &front = *item->front();
			if (item->symbol == LLVMTOK_NAME) {
				name = front.lexerInfo;
				break;
			}
		}
		// 	const ASTNode &front = *item->front();
		// 	switch (item->symbol) {
		// 		case LLVMTOK_TAG:
		// 			tag = front.lexerInfo;
		// 			break;
		// 		case LLVMTOK_SIZE:
		// 			size = front.atoi();
		// 			break;
		// 		case LLVMTOK_BASETYPE:
		// 			if (front.symbol == LLVMTOK_INTBANG)
		// 				baseType = front.atoi();
		// 			break;
		// 		case LLVMTOK_NAME:
		// 			name = front.lexerInfo;
		// 			break;
		// 		case LLVMTOK_FILE:
		// 			file = front.atoi();
		// 			break;
		// 		case LLVMTOK_LINE:
		// 			line = front.atoi();
		// 			break;
		// 		case LLVMTOK_SCOPE:
		// 			scope = front.atoi();
		// 			break;
		// 		case LLVMTOK_OFFSET:
		// 			offset = front.atoi();
		// 			break;
		// 		case LLVMTOK_FLAGS:
		// 			for (const ASTNode *pipe: front)
		// 				flags.insert(pipe->lexerInfo);
		// 			break;
		// 		case LLVMTOK_EXTRADATA:
		// 			if (front.symbol == LLVM_CONSTANT)
		// 				extraData = Constant::make(&front);
		// 			else
		// 				extraData = front.atoi();
		// 			break;
		// 		case LLVMTOK_ALIGN:
		// 			align = front.atoi();
		// 			break;
		// 		default:
		// 			throw std::runtime_error("Unrecognized symbol in DerivedType constructor: " +
		// 				std::to_string(item->symbol));
		// 	}
		// }
	}
}
